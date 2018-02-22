run() {
  CURRENT_DIR=`pwd`
  echo $CURRENT_DIR
  cd ~/rpi_explore
  make
  cd $CURRENT_DIR
  sudo ~/rpi_explore/a.out
}
