# SpellChecker

A basic spell checker written in C.

It allows you to check for any mistake in a text file using a dictionary (either the default one at /usr/share/dict/words or the one you supplied). It counts ' as a part of the word read so your dictionary must supply all words declination such as artisan's, artist's, etc...

## Warning

When parsing the dictionary, it rejects all words containing any accents such as é, è, à, ù, ê, etc... This is a functionnality which needs to be implemented in the future to allow more languages support.
