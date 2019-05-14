Command Line Interface
===============================================================================

**htr**
    Prints the habit completion table

**htr help**
    Prints help message

**htr version**
    Prints program version

**htr init <filename>**
    Creates new empty database under path specified in <filename>. If file
    already exists no action taken

**htr add <name>**
    Adds new habit to the database

**htr <habit_id> done**
    Sets habit selected by filter as done for today. The only possible value in
    filter is habit id (at least for now :))

**htr list**
    Print all habits in terminal
