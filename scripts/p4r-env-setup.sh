#!/bin/bash
startup_path=$_
if [[ $startup_path != *"/bash" ]]; then
    echo "Please run with bash"
    return
fi
script_folder=$0
script_folder="$( cd "$( dirname "$script_folder" )" >/dev/null 2>&1 && pwd )"
if ! echo $script_folder | grep "scripts" > /dev/null; then
    echo "Please run: bash $0"
    exit 1
fi

if ! grep "p4r-env-setup.sh" ~/.bashrc > /dev/null || test $1; then
# Section only needed for the CAEN Lab computers
#     profileAddition="
# if [ -f /usr/bin/modulecmd ] ; then
#     module load gcc/9.1.0
#     module load git/2.14.1
#     module load vscode/1.32.3
#     module load cmake/3.12.0
# fi

    bashprofileAddition="
# Added by p4r-env-setup.sh
if [ -f \$HOME/.bashrc ]; then
    source \$HOME/.bashrc
fi
"

    zshprofileAddition="
# Added by p4r-env-setup.sh
if [ -f \$HOME/.zshrc ]; then
    source \$HOME/.zshrc
fi
"

    bashrcAddition="
# Added by p4r-env-setup.sh
export PS1='\[\e]0;\u: \w\a\]\[\033[01;32m\]\u\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
export PATH=$script_folder:\$PATH
"

    zshrcAddition="
# Added by p4r-env-setup.sh
export PATH=$script_folder:\$PATH
"

    echo "$bashprofileAddition" >> ~/.bash_profile
    echo "$bashrcAddition" >> ~/.bashrc

    if which zsh ; then
        echo "$zshprofileAddition" >> ~/.zprofile
        echo "$zshrcAddition" >> ~/.zshrc
        echo "Success!"
        echo "Now run 'source ~/.zshrc' if you are using zsh"
        echo "or 'source ~/.bashrc' if you are using bash"
    else
        echo "Success!"
        echo "Now run 'source ~/.bashrc' and you will be done"
    fi

else
    echo "no changes made"
fi
