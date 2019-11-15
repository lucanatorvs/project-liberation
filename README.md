# Project Liberation
Project Liberation is een weerstation welke doormiddel van een ESP-32 over WiFi
de meet-data naar het Britse meteorologisch instituut
([MetOffice](https://www.metoffice.gov.uk/)) communiceert zodat deze beschikbaar
worden in de [WOW-NL](https://wow.knmi.nl/) database van de KNMI.

## Keeping our logs clean
Please read this and keep it in mind when writing commit messages:
[How to Write a Git Commit Message](https://chris.beams.io/posts/git-commit/)

Also, please put this in your `~/.gitconfig` (if you care why read 
[this](https://kalamuna.atlassian.net/wiki/display/KALA/Git+Workflow)):
```
[branch]
  autosetuprebase = always
[core]
  mergeoptions = --no-commit --no-ff
```

## Contibuting
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Licence
[MIT](LICENCE)
