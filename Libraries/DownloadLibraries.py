import os


def downloadFromGithub(name, version, tag, githubLink):
    print("Downloading {0} library in version {1}".format(name, version))

    cloneCmd = "git clone --no-checkout {0} {1}-{2}"
    checkoutCmd = "cd {0}-{1} && git checkout -q {2}"

    os.system(cloneCmd.format(githubLink, name, version))
    os.system(checkoutCmd.format(name, version, tag))

    print("Done\n")


downloadFromGithub(
    "fmt", "6.0.0", "6.0.0", "https://github.com/fmtlib/fmt.git")
downloadFromGithub(
    "googletest", "1.10.0", "release-1.10.0",
    "https://github.com/google/googletest.git")
downloadFromGithub(
    "date", "2.4.1", "v2.4.1",
    "https://github.com/HowardHinnant/date.git")