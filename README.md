# projlist

A short and simple program for recursively listing git repositories.

Unlike POSIX `find`, it recurses to arbitrary depth while efficiently detecting
git repositories, making it faster and more reliable than cobbled-together shell
scripts.

## Building

### Prerequisites

* Development headers and binaries for boost/system and boost/filesystem.
  (Ubuntu/Debian APT package name: `libboost-system-dev` and
  `libboost-filesystem-dev`)
* A C++ compiler compatible with the C++11 standard.
* GNU make

In order to build from git, you will additionally need

* GNU Autotools (Ubuntu/Debian APT package name: `autoconf` and `automake`)

#### Why boostlib?

C++17 will finally be adding a standard filesystem library (in fact, they
actually just standardized the boost filesystem library). However, in C and in
previous versions of C++, there was no standard way to iterate over files in a
directory, i.e. everything this program does.

Since C++17 support is limited at the moment, this program will continue to use
boost/filesystem for the foreseeable future.

### Build instructions

If building from git:

* `autoreconf -i`

Then:

* `./configure`
* `make`

### Installation

* `make install`

You can set the installation prefix in the usual way (i.e. `./configure
--prefix=/path/to/dir`)

### Building a distribution

* `make dist`

## Running

Usage is `projlist /path/to/root/directory`. The program will search that
directory recursively, printing each git repository it finds. In my experience,
the first usage on any given session will be slow as the kernel has to retrieve
the directory inodes from the disk, but subsequent uses will be
near-instantaneous because the inodes are already cached.

Since it will recurse to arbitrary depth, running it on a directory like, say,
`~` is ill-advised.

## Example usages

Assuming the executable is named `projlist` and is on the PATH:

### bash/zsh function

This pipes the output of `projlist` into
[selecta](https://github.com/garybernhardt/selecta), then switches to the
selected directory:

```sh
proj() {
    # or whatever directory you want
    cd $( projlist ~/Projects | selecta )
}
```

### Emacs Helm source

This uses the output of `projlist` to build a
[helm](https://github.com/emacs-helm/helm) session for fuzzy matching on the
results, and opens a dired buffer on the selected directory:

```elisp
(defun helm-projlist ()
  (interactive)
  (find-file
   (helm :sources (helm-build-sync-source "Projects tree"
                    :candidates (split-string
                                 (shell-command-to-string "projlist ~/Projects")
                                 "\n"
                                 t)
                    :fuzzy-match t)
         :buffer "*helm projlist*")))
```

You can then bind `helm-projlist` to a key as desired.

## To-do list

* Adding support for a maximum depth for sanity purposes is probably a good
  idea, especially if someone has a really messy project directory (e.g. their
  projects are stored directly in `~`).
* Perhaps a few more features of `find` - I don't intend this to become a
  full-on `find` replacement, but I could see some `find` options like `-print0`
  being useful enough to be worth implementing.
