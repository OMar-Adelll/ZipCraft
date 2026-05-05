from __future__ import annotations

import shutil
import subprocess
import os
import tempfile
from pathlib import Path
import tkinter as tk
from tkinter import messagebox, ttk


class CompressionGUI:
    def __init__(self, root: tk.Tk) -> None:
        self.root = root
        self.root.title("ZipCraft Text Compression")
        self.root.geometry("900x650")
        self.root.minsize(720, 520)

        self.project_root = Path(__file__).resolve().parent.parent
        self.algorithms_dir = self.project_root / "algorithms"

        self.algorithms = {
            "Run-Length Encoding (1-rle.cpp)": "1-rle.cpp",
            "Simple Repetition Suppression (2-srs.cpp)": "2-srs.cpp",
            "Pattern Substitution / LZ77 (3-Pattern-Substitution.cpp)": "3-Pattern-Substitution.cpp",
            "Fixed Length (4-fixed-length.cpp)": "4-fixed-length.cpp",
            "Variable Length (5-variable-length.cpp)": "5-variable-length.cpp",
            "Shannon-Fano (6-shannon-fano.cpp)": "6-shannon-fano.cpp",
            "Huffman (7-huffman.cpp)": "7-huffman.cpp",
        }

        self.selected_algorithm = tk.StringVar(value=next(iter(self.algorithms)))

        self._build_ui()

    def _build_ui(self) -> None:
        container = ttk.Frame(self.root, padding=16)
        container.pack(fill="both", expand=True)

        ttk.Label(
            container,
            text="Input Text",
            font=("TkDefaultFont", 11, "bold"),
        ).pack(anchor="w")

        self.input_text = tk.Text(container, height=10, wrap="word")
        self.input_text.pack(fill="both", expand=True, pady=(6, 14))

        controls = ttk.Frame(container)
        controls.pack(fill="x", pady=(0, 14))

        ttk.Label(controls, text="Algorithm:").pack(side="left")

        algorithm_menu = ttk.Combobox(
            controls,
            textvariable=self.selected_algorithm,
            values=list(self.algorithms.keys()),
            state="readonly",
            width=48,
        )
        algorithm_menu.pack(side="left", padx=(8, 12))

        self.run_button = ttk.Button(controls, text="Run", command=self.run_selected_algorithm)
        self.run_button.pack(side="left")

        ttk.Label(
            container,
            text="Output",
            font=("TkDefaultFont", 11, "bold"),
        ).pack(anchor="w")

        self.output_text = tk.Text(container, height=14, wrap="word", state="disabled")
        self.output_text.pack(fill="both", expand=True, pady=(6, 0))

    def set_output(self, text: str) -> None:
        self.output_text.config(state="normal")
        self.output_text.delete("1.0", tk.END)
        self.output_text.insert("1.0", text)
        self.output_text.config(state="disabled")

    def run_selected_algorithm(self) -> None:
        input_data = self.input_text.get("1.0", tk.END).rstrip("\n")
        if not input_data.strip():
            messagebox.showwarning("Empty Input", "Please enter some text before running an algorithm.")
            return

        compiler = shutil.which("g++")
        if compiler is None:
            self.set_output("Error: g++ was not found in PATH.")
            return

        source_name = self.algorithms[self.selected_algorithm.get()]
        source_path = self.algorithms_dir / source_name

        if not source_path.exists():
            self.set_output(f"Error: source file was not found:\n{source_path}")
            return

        self.run_button.config(state="disabled")
        self.set_output("Compiling and running the selected algorithm...")
        self.root.update_idletasks()

        try:
            result = self.compile_and_run(compiler, source_path, input_data)
        except subprocess.TimeoutExpired:
            result = "Runtime failed\n\nThe selected program exceeded the 10 second execution limit."
        finally:
            self.run_button.config(state="normal")

        self.set_output(result)

    def compile_and_run(self, compiler: str, source_path: Path, input_data: str) -> str:
        with tempfile.TemporaryDirectory(prefix="zipcraft_") as temp_dir:
            executable_name = "algorithm_runner.exe" if self._is_windows() else "algorithm_runner"
            executable_path = Path(temp_dir) / executable_name

            compile_command = [
                compiler,
                str(source_path),
                "-std=c++17",
                "-O2",
                "-o",
                str(executable_path),
            ]

            compile_process = subprocess.run(
                compile_command,
                capture_output=True,
                text=True,
                cwd=self.project_root,
                check=False,
            )

            if compile_process.returncode != 0:
                return self.format_error(
                    title="Compilation failed",
                    command=compile_command,
                    stdout=compile_process.stdout,
                    stderr=compile_process.stderr,
                    returncode=compile_process.returncode,
                )

            run_process = subprocess.run(
                [str(executable_path)],
                input=input_data,
                capture_output=True,
                text=True,
                cwd=self.project_root,
                check=False,
                timeout=10,
            )

            if run_process.returncode != 0:
                return self.format_error(
                    title="Runtime failed",
                    command=[str(executable_path)],
                    stdout=run_process.stdout,
                    stderr=run_process.stderr,
                    returncode=run_process.returncode,
                )

            output = run_process.stdout.strip()
            if not output:
                return "Program finished successfully, but it produced no stdout output."

            return output

    @staticmethod
    def format_error(
        *,
        title: str,
        command: list[str],
        stdout: str,
        stderr: str,
        returncode: int,
    ) -> str:
        parts = [
            title,
            f"Return code: {returncode}",
            f"Command: {' '.join(command)}",
        ]

        if stdout.strip():
            parts.append("stdout:\n" + stdout.strip())

        if stderr.strip():
            parts.append("stderr:\n" + stderr.strip())

        return "\n\n".join(parts)

    @staticmethod
    def _is_windows() -> bool:
        return os.name == "nt"


def main() -> None:
    root = tk.Tk()
    app = CompressionGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
