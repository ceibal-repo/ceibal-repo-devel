Start the new machine and log in:

    ssh root@<ipaddr>
    mkdir .ssh
    chmod 700 .ssh
    exit

Enable SSH login thru public key:

    scp ~/.ssh/id_rsa.pub root@<ipaddr>:.ssh/authorized_keys
    ssh root@<ipaddr>
    chmod 600 .ssh/authorized_keys
    exit

Copy (or generate a new) rsync SSH private key that allowed for the rsync user on the repository master:

    scp /root/.ssh/rsync_dsa root@<ipaddr>:.ssh/rsync_dsa

Configure the repo. To do so, copy `ceibal-setup-repoclient` from an existing install and run the script:

    scp /usr/bin/ceibal-setup-repoclient root@<ipaddr>:
    ssh root@<ipaddr>
    ./ceibal-setup-repoclient

Install ceibal-repo-devel:

    apt-get update
    apt-get install ceibal-repo-devel --assume-yes
    
Run the setup mirror script (will rsync against the master repo):

    ceibal-setup-mirror

Run the rsync script for the first time:

    ceibal-rsync-mirror

Configure no ip dyndns client (or your own DNS server) https://www.noip.com/support/knowledgebase/installing-the-linux-dynamic-update-client-on-ubuntu/, or copy precompiled binary from existing server from /usr/local/bin/noip2

Edit /etc/ssh/sshd_config and change port to 3022.

    sed -i -e 's,^#\?Port 22$,Port 3022,' /etc/ssh/sshd_config
    service ssh reload

(Optional) Add an entry on your local ~/ssh/config, like:
    Host ceibal2
        HostName apt2.ceibal.edu.uy
        User root
        Port 3022
        ForwardAgent yes
