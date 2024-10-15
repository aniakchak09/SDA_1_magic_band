# Magic Band

This project is a C-based application that simulates a Turing machine. The Turing machine is a theoretical device that manipulates symbols on a strip of tape according to a table of rules. Despite its simplicity, a Turing machine can be adapted to simulate the logic of any computer algorithm.

## Project Structure

The project is structured around several key data structures and functions, all defined in the `functii.h` file. The main data structures are:

- `TCelula2` and `TLista2`: These structures represent a doubly linked list with a sentinel node. This list is used to simulate the tape of the Turing machine.
- `TBanda`: This structure represents the tape of the Turing machine, including a sentinel node and a "finger" that points to the current position on the tape.
- `TCelula` and `TLista`: These structures represent a singly linked list used for various operations.
- `TCoada`: This structure represents a queue used for various operations.
- `TStiva`: This structure represents a stack used for various operations.

The main functions are:

- `MOVE_RIGHT` and `MOVE_LEFT`: These functions move the "finger" of the Turing machine to the right or left on the tape.
- `MOVE_RIGHT_CHAR` and `MOVE_LEFT_CHAR`: These functions move the "finger" to the right or left until a specified character is found.
- `WRITE`: This function writes a character at the current position on the tape.
- `INSERT_LEFT` and `INSERT_RIGHT`: These functions insert a character to the left or right of the current position on the tape.
- `SHOW_CURRENT` and `SHOW`: These functions display the current character or the entire tape.
- `UNDO` and `REDO`: These functions undo or redo the last operation.
- Queue and stack operations: These functions perform various operations on queues and stacks.

## Usage

This project is intended to be used as a learning tool for understanding the workings of a Turing machine.
