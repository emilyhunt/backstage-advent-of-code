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

#### Instructions on how to add repos as submodules (for contributors only)
<details>
<summary>(Click to show)</summary>

If you're a repo contributor, then you can add a new submodule with [`git submodule add`](https://git-scm.com/docs/git-submodule#Documentation/git-submodule.txt-add-bltbranchgt-f--force--nameltnamegt--referenceltrepositorygt--depthltdepthgt--ltrepositorygtltpathgt). 

#### 1. Add the repo

Ensure that the correct branch name is specified -- **this is typically `main` for newer repos** -- else updating won't necessarily work.

```
git submodule add -b <branch> https://github.com/<username>/<repo_name> <name>
```

(The branch issue can be fixed afterwards with [these instructions](https://stackoverflow.com/questions/1777854/how-can-i-specify-a-branch-tag-when-adding-a-git-submodule/18799234#18799234).)

#### 2. Commit the changes

Make a new commit with the new submodule added.

#### 3. Check that the new submodule can be updated

Check that trying to update all modules works. The following should return no errors, and should update all submodules:

```
git submodule update --remote --merge
```

If this works, then you're safe to commit the changes to the `main` branch. (If not, undo your changes and chat to Emily.)

</details>

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

Each year, we use a private leaderboard. They're currently maintained by [Tom](https://github.com/TomDufall) - ask him to get added.

Links to each year's leaderboard (you'll need to be logged in to see them):

* **[2022](https://adventofcode.com/2022/leaderboard/private/view/830486)**
* [2021](https://adventofcode.com/2021/leaderboard/private/view/830486)
* [2020](https://adventofcode.com/2020/leaderboard/private/view/830486)
* [2019](https://adventofcode.com/2019/leaderboard/private/view/830486)
* [2018](https://adventofcode.com/2018/leaderboard/private/view/830486)
* [2017](https://adventofcode.com/2017/leaderboard/private/view/830486)
* [2016](https://adventofcode.com/2016/leaderboard/private/view/830486)
* [2015](https://adventofcode.com/2015/leaderboard/private/view/830486)


## Repo etiquette

This mostly applies to people not using submodules.

* Don't commit things to someone else's folder unless you want to be in _git merge hell_

* Check the `.gitignore` file and make sure that anything you don't want added to the entire repo (like compiled binaries) isn't shared with everyone else. [How to use `.gitignore` files](https://git-scm.com/docs/gitignore)

* Try to avoid adding any big files here! You can set up some `.gitignore` rules to keep them in your local repo if you'd like.

* Make sure that any file output that your code spews out goes into any folder called `output`, as this will be auto-ignored via the .gitignore file.


## Workflow structure

The repo has a number of workflows setup to automatically sync submodules.

1. Once every hour during December (or daily otherwise, set manually), `.github/workflows/main.yml` checks all submodules for changes and creates PRs.
2. `.github/workflows/pr-labeler.yml` labels relevant PRs.
3. `.github/workflows/automerge.yml` merges them into the `main` branch.

Chat to Emily if there are any configuration issues or to get things tweaked.
