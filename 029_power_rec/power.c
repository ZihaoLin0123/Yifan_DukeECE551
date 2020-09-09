unsigned power(unsigned x, unsigned y){
  if(y == 0 || y == 1){
    return x;
  }

  return x * power(x, y - 1);
}
