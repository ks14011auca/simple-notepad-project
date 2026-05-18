# Notepad Project

## Overview

In this project, I improved the Notepad application and added new features to make it work more like a small WordPad
editor.

The program can already open and save files, edit text, format text, use find and replace, count word frequency, and
show word and line counts. For this project, I added exception handling, a spell checker, and some optional features.

## Required Feature 1: Exception Handling

I added exception handling for file operations.

The exception classes are in `notepad_exception.h`. There is one main exception class called `notepad_exception`, and
three more specific classes:

- `file_not_found_exception`
- `file_read_exception`
- `file_write_exception`

I used these exceptions in `open_file()` and `save_file()`.

For example, if the program cannot open a file, read a file, or save a file, it throws an exception. Then the exception
is caught with a `catch` block, and the program shows an error message with `QMessageBox::critical`.

The error message window uses the title `Error`, because this was required in the project description.

I chose this design because it makes the code easier to understand. The program checks for file problems in one place
and shows the error message in a clear way.

## Required Feature 2: Spell Checker

I added a spell checker using the file `data/words.txt`.

I created two classes for this feature:

- `spell_checker`
- `spell_checker_highlighter`

The `spell_checker` class loads all words from `data/words.txt` into a `std::set`. It checks if a word exists in the
dictionary or not.

The `spell_checker_highlighter` class uses `QSyntaxHighlighter`. It goes through the text in the editor and underlines
misspelled words in red.

I also added `Tools > Check Spelling...`. This menu option runs the spell check again for the whole document.

When the user right-clicks a misspelled word, the program shows a menu with spelling suggestions. If the user clicks a
suggestion, the wrong word is replaced. I also added an `Ignore` option. If the user chooses `Ignore`, the word is no
longer underlined.

## Optional Feature 1: Cursor Line and Column Indicator

I added more information to the status bar.

The status bar now shows:

`Words: N  Total lines: N  Cursor: line:column`

This means the user can see the number of words, the total number of lines, and the current cursor position.

This updates when the user types text or moves the cursor.

I chose this feature because it is useful when working with longer text.

## Optional Feature 2: Font Dialog

I added `Format > Font...`.

This opens a font dialog. The user can choose a font, and the program applies it to the selected text.

If no text is selected, the font is applied to the whole document.

I used `QFontDialog` and `QTextCharFormat` for this feature.

## Optional Feature 3: Text Color Picker

I added `Format > Text Color...`.

This opens a color dialog. The user can choose a text color, and the program applies it to the selected text.

If no text is selected, the color is applied to the whole document.

I used `QColorDialog` and `QTextCharFormat` for this feature.

## Optional Feature 4: Zoom

I added a new `View` menu with these actions:

- `Zoom In`
- `Zoom Out`
- `Reset Zoom`

`Zoom In` makes the text bigger on the screen.  
`Zoom Out` makes the text smaller on the screen.  
`Reset Zoom` returns the text size back to normal.

I used a variable called `zoom_steps` to remember how much the text was zoomed in or out. This helps the program reset
the zoom correctly.

## How to Build

The project can be built with these commands:

```bash
cmake -S . -B build
cmake --build build
```

## Important Note

The working directory should be set to:

`$ProjectFileDir$`

This is important because the program needs to find these files:

- `data/words.txt`
- `data/images/bold.svg`
- `data/images/italic.svg`
- `data/images/underline.svg`