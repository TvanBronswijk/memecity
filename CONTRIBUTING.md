Two things you should never do in git:
* NEVER force a push. If you find yourself in a situation where your changes can't be pushed upstream, something is wrong. Contact the configuration manager.
* NEVER rebase a branch that you pushed, or that you pulled from another person. Rebasing published branches can lead to duplicate commits in the shared repository.

In general, the preferred workflow is:
* Create a branch from develop, check it out, do your work.
* Test and commit your changes.
* Push the changes to your remote branch.
* Open up a Pull Request if you think your code is ready for review.
* Once your code is reviewed by at least one person, and merged into develop, the remote branch will be **deleted**.
* Delete the local branches whose changes have been merged into develop, and do a `git pull` to get the newest code.

__Some useful terms:__

**master**: this is the main code branch. Branches are generally created off of master, ***but*** in our case, we'll probably base them off develop most of the times, and at the end of the line, we'll create a release branch with the latest stable build of the project, or push it to master.

**origin**: the default remote repository that all your branches are pulled from and pushed to. This is defined when you execute the initial git clone command.

**unpublished vs. published branches**: an unpublished branch is a branch that only exists on your local workstation, in your local repository. Nobody but you know that branch exists. A published branch is one that has been pushed up to GitHub, and is available for other group members to checkout and work on.

To list all branches: `git branch`

To *just* create a new branch: `git branch feature/my-branch`

Check out to your branch: `git checkout feature/my-branch`

To create a new branch and immediately check it out: `git checkout -b feature/add-flying-unicorns`

*Please don't forget the "feature/" or "hotfix/" in front of your branch name.*

To commit: `git commit -m 'Added something cool.`

*I don't really mind if you do or do not finish your commit message with a period, but at least do capitalize the first letter to keep things consistent with what we've already adopted.*

To push: `git push`

To pull: `git pull`

*Yep.*

To delete a local branch: `git branch -d feature/my-feature-branch`

To delete a remote branch: `git branch -dr origin/feature/my-feature-branch` (be careful with that)


