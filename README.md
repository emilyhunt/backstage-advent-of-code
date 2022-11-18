# Backstage Does Advent of Code!
This repo collects various attempts at the [advent of code](https://adventofcode.com/) by friends from [Backstage](https://www.bts-crew.com/) at the UoBath SU.

## Set-up guide

### 1. Clone the whole repo

To clone the repo and all of its constituent submodules, use:

```
git clone --recursive https://github.com/emilyhunt/backstage-advent-of-code.git
```

If you didn't do this, then depending on your Git version, the submodules may need to be initialised for the first time with:

```
git submodule update --init
```

It's not the end of the world if you don't update the submodules, you just won't see much in your local repo!

### 2. Make your own submodule

We now strongly recommend using a personal **git submodule** to store your code. This way, updates to the main branch aren't necessary, and permissions can be controlled in a more granular and straightforward way. More info on submodules can be found [here](https://github.blog/2016-02-01-working-with-submodules/).

The short instructions are...

1. Initialise your own blank repository. Call it something useful, like "advent-of-code".

2. Ask Emily to add your repository as a submodule to this parent one!

#### (Aside for contributors only)

If you've been added to the repo as a contributor, then you can run the following in this repo to do it yourself:

```
git submodule add https://github.com/<username>/<repo_name> <name>
```

Don't forget to commit the change to the `main` branch.

### 3. Setup your submodule's structure

You can structure your submodule code however you'd like, but we recommend doing something like this for consistency with others:

```
/NAME                - your submodule
/NAME/README.md      - general info about what you're doing
/NAME/YEAR/README.md - optional readme for each year, with e.g. info on which language is being used and how to run it
/NAME/YEAR/XX        - code & data for each day, where XX is e.g. 01, 02, 03... etc.
/NAME/YEAR/XX/data   - your data for the day
/NAME/YEAR/XX/output - any output for that day that should be ignored and not be added to the repo
```

### 4. Get added to the private leaderboard

Each year, we use a private leaderboard. They're currently maintained by [Tom](https://github.com/TomDufall) - ask him to get added. You'll need to be logged in to see it.

Links to each year's leaderboard:

* 2022 (in-progress)
* [2021](https://adventofcode.com/2021/leaderboard/private/view/830486)
* 2020 (link unknown)


## Repo etiquette

This mostly applies to people not using submodules.

* Don't commit things to someone else's folder unless you want to be in _git merge hell_

* Check the `.gitignore` file and make sure that anything you don't want added to the entire repo (like compiled binaries) isn't shared with everyone else. [How to use `.gitignore` files](https://git-scm.com/docs/gitignore)

* Try to avoid adding any big files here! You can set up some `.gitignore` rules to keep them in your local repo if you'd like.

* Make sure that any file output that your code spews out goes into any folder called `output`, as this will be auto-ignored via the .gitignore file.
