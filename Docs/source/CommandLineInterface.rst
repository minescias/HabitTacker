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

    Availiable options:
     *  -target=<target> - set daily target for this habit (dafault 1)

**htr <habit_id> edit <options>**
    Edits habit with given ID

    Availiable options:
     *  -name=<new name> - sets new habit name

**htr <habit_id> done <options>**
    Sets habit selected by filter as done for today. The only possible value in
    filter is habit id

    Availiable options:
     *  -reset - delete habit if set
     *  -date=<date> - set habit for given date (default today)
     *  -result=<result> - set result for given day (default current target)

**htr list**
    Print all habits in terminal

Date options
 *  today
 *  yesterday
 *  tomorrow
 *  date in format 'DD-MM-YYYY'
