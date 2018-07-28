run() {
  CURRENT_DIR=`pwd`
  echo $CURRENT_DIR
  cd ~/rpi_explore
  make
  cd $CURRENT_DIR
  sudo ~/rpi_explore/a.out
}

putrpio() {
#!/bin/sh
HOST='192.168.1.108'
USER='pi'
PASSWD='rpi123'
FILE='rpio'

ftp -n $HOST <<END_SCRIPT
quote USER $USER
quote PASS $PASSWD

put $FILE

quit
END_SCRIPT
bash
exit 0
}


