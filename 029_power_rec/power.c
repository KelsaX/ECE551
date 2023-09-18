unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }

  /*
我们思考一下power是怎么计算的---比如x的y次方就是x与x相乘乘y次
   */
  return x * power(x, y - 1);
}
