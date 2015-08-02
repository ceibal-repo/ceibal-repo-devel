
REPO_SERVER=apt.ceibal.edu.uy
if [ -f /etc/ceibalrepo.conf ]; then
    . /etc/ceibalrepo.conf
fi

if [ -f ~/.ceibalrepo ]; then
    . ~/.ceibalrepo
fi

# Taken from https://wiki.ubuntu.com/PbuilderHowto#Multiple_pbuilders 
# Only considering Ubuntu builds.

HOOKDIR="/etc/pbuilder/hooks/"

# List of Ubuntu suites. Update these when needed.
UBUNTU_SUITES=("saucy" "raring" "precise")
# Update to preferred mirror.
UBUNTU_MIRROR="uy.archive.ubuntu.com"

OTHERMIRROR="deb http://${REPO_SERVER}/ubuntu/ ${REPO_CODENAME} main"
ALLOWUNTRUSTED=yes
APTKEYRINGS=("/usr/share/keyrings/ubuntu-archive-keyring.gpg" "/usr/share/keyrings/ceibal-repo-keyring.gpg")

# Set the architecture to the host architecture if none set.
#: ${ARCH:="$(dpkg --print-architecture)"}
# Using a default of i386 when ARCH is not given.
: ${ARCH:="i386"}

# Default to Ubuntu precise.
: ${DIST:="precise"}

NAME="$DIST"
if [ -n "${ARCH}" ]; then
    NAME="$NAME-$ARCH"
    DEBOOTSTRAPOPTS=("--arch" "${ARCH}" "${DEBOOTSTRAPOPTS[@]}")
fi
PDEBUILD_PBUILDER=cowbuilder
# BASETGZ="/var/cache/pbuilder/$NAME-base.tgz"
# Optionally, set BASEPATH (and not BASETGZ) if using cowbuilder
BASEPATH="/var/cache/pbuilder/$NAME/base.cow/"
DISTRIBUTION="$DIST"
BUILDRESULT="/var/cache/pbuilder/$NAME/result/"
APTCACHE="/var/cache/pbuilder/$NAME/aptcache/"
BUILDPLACE="/var/cache/pbuilder/build/"

# Ubuntu configuration
MIRRORSITE="http://$UBUNTU_MIRROR/ubuntu/"
COMPONENTS="main restricted universe multiverse"
DEBOOTSTRAPOPTS=("${DEBOOTSTRAPOPTS[@]}" "--keyring=/usr/share/keyrings/ubuntu-archive-keyring.gpg")

CCACHEDIR=/var/cache/pbuilder/ccache

