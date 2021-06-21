#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct Matrix {
    short size;
    int** elem;
    long long trace;
} Matrix;

int main(void) {
  Matrix Mat;

  // char path_inp = @"matrix.in";
  // string path_out = @"trace.out";

  BinaryReader reader = new BinaryReader(File.Open(@"matrix.in", FileMode.Open));
  BinaryWriter writer = new BinaryWriter(File.Open(@"trace.out", FileMode.OpenOrCreate));

  while (reader.PeekChar() > -1)
  {
      short size = reader.ReadInt16();

      Mat.size = size;
      Mat.elem = (int**) calloc(size, sizeof(int*));
      for (int i = 0; i < size; i++) {
        Mat.elem[i] = (int*) calloc(size, sizeof(int));
      }

      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          Mat.elem[i][j] = reader.ReadInt32();
        }
      }

      string capital = reader.ReadString();
      int area = reader.ReadInt32();
      double population = reader.ReadDouble();
  }

  Mat.trace = 0;
  for (int i = 0; i < Mat.size; i++) {
    Mat.trace += Mat.elem[i][i];
  }

  writer.Write(Mat.trace);
}
