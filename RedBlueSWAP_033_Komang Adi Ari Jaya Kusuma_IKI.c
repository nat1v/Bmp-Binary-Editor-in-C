#include <stdio.h>
#include <stdlib.h>

FILE* imageIn;
FILE* imageOut;

// MUST DO! to SWAP COLOR merah ama biru;
// baca header bmp di file bmp?!!!
// cari dimensi gambarnya
// check jika 32 bit bmp, jika 24-bit atau lainnya break.
// cari info padding per warna
// 1 pixel = 4 bytes (RGB + A) a itu alpha
// _033_komang adi ari jaya kusuma_ proudly made with nvim;;

int main(){
  
  imageIn = fopen("CONTOH_FILE.bmp", "rb");//baca isi file dalam mode binary
      if (!imageIn){
          printf("tidak ada file \"CONTOH_FILE.bmp\" disini, coba buat (32-bit format pls)");
          fclose(imageIn);
  }
  imageOut = fopen("Output.bmp", "wb");//tulis atau write file dalam mode binary

  char header[54]; //total size bmp + info(DIB) header
  fread(header, 1, 54, imageIn); //membaca 54bytes dari file imageIn dan memasukkannya ke header
  fwrite(header, 1, 54, imageOut); //menulis file 54bytes dari header ke imageOut


  //refernsi DIB HEADER source: wikipedia::BMP
  int lebar = *(int *)&header[18]; //offset byte ke 18; sesuuai dengan source = width
  int tinggi = *(int *)&header[22]; //offset byte ke 22; source::height, atau tinggi
  int bpp =  *(int *)&header[28]; ///offset byte ke 28; source::bpp atau bits per pixel

  if (bpp =! 32){ // mengecek apakah file adalah 32 bit bmp; jika bukan....
    printf("ini bukan 32-bit bmp");
    fclose(imageIn);
    fclose(imageOut);
    return 1; // exit;
  }

  // penjelasan:  ketiga int diatas membaca masing2 info DIB_HEADER bmp ke kategorinya masing masing
  //              &header adalah pointer ke address variabel header.
  //              variable di cast ke bentuk int jadi compiler mengira itu adalah pointer to int?
  //              *didepan berarti dereference berarti mengambil data di address tersebut


  int ukuranBaris = lebar * 4; //di 32-bit BMP, setiap pixel mempunyai 4 bits, jadi (lebar x 4) = ukuran 1 baris dari gambar
  //4 bit pixel (Blue, Red, Green, Alpha(transparency))

  char *baris = (char*)malloc(ukuranBaris); //baris adalah pointer yang menyimpan alamat memory, yang memorynya sebesar variable sizeBaris, lalu casting ke char
  
  // loop luar
  for (int y = 0; y < tinggi; y++)
  { 
      fread(baris, 1, ukuranBaris, imageIn);//membaca 1 baris dari gambar 1 pixel dari kiri ke kanan?
      //loop inti
      for(int x = 0; x < lebar; x++)
      {
      
      // membuat pointer yang menyimpan alamat pixel yang dimana  x adalah posisi sebuah pointer menunjuk sebuah pixel di loop luar;
          char *pixel = &baris[x * 4];
      
          //pixel swapping, biru<>merah, dengan posisi pointer di y pixel
          char pixel_sementara = pixel[0]; //simpan pixel biru
          pixel[0] = pixel[2]; //pixel biru == merah
          pixel[2] = pixel_sementara; // merah == biru;

      }
    
      fwrite(baris, 1, ukuranBaris, imageOut); //mengwrite 1 baris yang sudah di modif ke imageOut

  }

  free(baris); //agar tidak ada memory bocor
  fclose(imageIn);
  fclose(imageOut);
  //tutup file agar gak bentrok dengan process lain di OS;   

  return 0;
}
