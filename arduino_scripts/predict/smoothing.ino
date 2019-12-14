// smooth out measurement errors

void smooth(short* dimension_data) {

  for (short i=0; i<steps; i++) {
    if (dimension_data[i] < smoothing) {
      dimension_data[i] = 0;
    }
  }
}
