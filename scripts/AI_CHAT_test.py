import sys

class Printer:
    def __init__(self, string):
        self.string = string

    def print_to_stdout(self):
        print(self.string.encode('utf8'))

if __name__ == "__main__":
    input_string = sys.argv[1]
    printer = Printer(input_string)
    printer.print_to_stdout()
