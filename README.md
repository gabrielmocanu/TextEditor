# TextEditor
A simple text editor like vim but without graphical user interface.

  We used two data structures: a doubly linked list with nodes that holds each character and a list of lists that always retains cursor position. Of course we have the insertion mode and the command mode and we can change between them by insert "::i".
  # Commands list:
    - u - undo
    - r - redo
    - s - save
    - q - quit
    - b - backspace
    - dl [ nr_line ] - delete line
    - gl nr_line - goto line
    - gc nr_char [ nr_line ] - goto character
    - d [ nr_chars ] - delete
    - re old_word new_word - replace
