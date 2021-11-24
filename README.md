# advent-of-code-21
Attempts at the [2021 advent of code!](https://adventofcode.com/2021/) Also, here's [our private leaderboard](https://adventofcode.com/2021/leaderboard/private/view/830486) on the AoC site (speak to Tom to get added.)

Chat to Emily to get added.

## Folder structure

Setup your folder like this:

```
/NAME           - your folder
/NAME/README.md - info about what you're doing this year, e.g. language used
/NAME/XX        - code & data for each day, where XX is e.g. 01, 02, 03... etc.
/NAME/XX/data   - your data for the day
/NAME/XX/output - any output for that day that should be ignored and not be added to the repo
```

## Repo etiquette

* Don't commit things to someone else's folder unless you want to be in _git merge hell_

* Check the `.gitignore` file and make sure that anything you don't want added to the entire repo (like compiled binaries) isn't shared with everyone else. [How to use `.gitignore` files](https://git-scm.com/docs/gitignore)

* Try to avoid adding any big files here! You can set up some `.gitignore` rules to keep them in your local repo if you'd like.

* Make sure that any file output that your code spews out goes into any folder called `output`, as this will be auto-ignored via the .gitignore file.

## Git submodules
The repo contains some [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules). To clone a repo with submodules, use `git clone --recurse-submodules`. If you didn't do this the submodule may need to be initialised first time with `git submodule update --init`. It's not the end of the world if you don't update the submodules though, you just won't see much in your local repo!
