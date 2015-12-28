# projlist

A short and simple program for recursively listing git repositories.

Unlike POSIX `find`, it recurses to arbitrary depth while efficiently detecting git repositories, making it faster and more reliable than cobbled-together shell scripts.

## Building

The build process is rudimentary, but functional.

### Prerequisites

* Development headers and binaries for boostlib. (Ubuntu/Debian APT package name: `libboost-all-dev`)
* A C++ compiler compatible with the C++11 standard. (`g++` with the `-std=c++11` switch meets this requirement)
* GNU make

### Build instructions

* Edit the Makefile as desired to select executable name and installation directory.
  * Depending on your choice of installation directory, you might also need to add `sudo` to the `install` and `clean` targets.
* `make && make install`

## Running

I recommend adding the executable to a directory in your PATH (`~/bin` is a good choice if you have that set up - and if you don't, why not?).

Usage is `projlist /path/to/root/directory`. The program will search that directory recursively, printing each git repository it finds. In my experience, the first usage on any given session will be slow as the kernel has to retrieve the directory inodes from the disk, but subsequent uses will be near-instantaneous because the inodes are already cached.

Since it will recurse to arbitrary depth, running it on a directory like, say, `~` is ill-advised.

## Example usages

Assuming the executable is named `projlist` and is on the PATH:

### bash/zsh function

This pipes the output of `projlist` into [selecta](https://github.com/garybernhardt/selecta), then switches to the selected directory:

```sh
proj() {
    # or whatever directory you want
    cd $( projlist ~/Projects | selecta )
}
```

### Emacs Helm source

This uses the output of `projlist` to build a [helm](https://github.com/emacs-helm/helm) session for fuzzy matching on the results, and opens a dired buffer on the selected directory:

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

* Adding support for other version control systems is something I want to do at some point, and it shouldn't take too long; if someone else wants to submit a pull request for their favorite VCS I'd be happy to merge it. Otherwise I'll probably get around to it eventually.
* Adding support for a maximum depth for sanity purposes is probably a good idea, especially if someone has a really messy project directory (e.g. their projects are stored directly in `~`).
* Perhaps a few more features of `find` - I don't intend this to become a full-on `find` replacement, but I could see some `find` options like `-print0` being useful enough to be worth implementing.
