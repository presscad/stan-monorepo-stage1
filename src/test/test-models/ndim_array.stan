data {
  int d1;
  int d2;
  int d3;
  int ar[d1, d2, d3];
}
transformed data {
  print("d1_1: ", ar[1]);
  print("d1_2: ", ar[2]);
}
