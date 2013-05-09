consolidate-templates
=====================

Bring html templates from one folder into one html file wraped in template divs (for underscore, handlebars, etc)

Components of this which must be set are:

- PATH , the path from the executable which points to the folder containing the html files (is non recursive)
- TARGET , the html file for which the html files are inserted
- opening tag , the opening tag which wraps the file contents (currently sets the filename as the id)
- closing tag , the closing tag which closes the opening tag
- targetString, the first element within TARGET where the consolidated file contents are inserted after


