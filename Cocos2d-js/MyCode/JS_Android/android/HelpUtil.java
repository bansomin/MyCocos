package org.cocos2dx.javascript;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.annotation.SuppressLint;
import android.content.ContentResolver;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.net.Uri;

public class HelpUtil {

    //根据图片路径获取本地图片的Bitmap
    public static Bitmap getBitmapByUrl(String url){
        FileInputStream fis = null;
        Bitmap bitmap = null;
        try {
            fis = new FileInputStream(url);
            bitmap = BitmapFactory.decodeStream(fis);
        }catch (FileNotFoundException e){
            e.printStackTrace();
            bitmap = null;
        }finally {
            if (fis!=null){
                try {
                    fis.close();
                }catch (IOException e){
                    e.printStackTrace();
                }
                fis = null;
            }
        }
        return  bitmap;
    }

    //bitmap旋转90度
    public static Bitmap createPhotos(Bitmap bitmap){

        if (bitmap!=null){
            Matrix m = new Matrix();
            try {
                m.setRotate(90, bitmap.getWidth()/2, bitmap.getHeight()/2);
                Bitmap bmp2 = Bitmap.createBitmap(bitmap, 0, 0, bitmap.getWidth(), bitmap.getHeight(), m, true);
                bitmap.recycle();
                bitmap = bmp2;
            }catch (Exception e){
                System.out.print("创建图片失败！" + e);
            }
        }
        return bitmap;
    }

    //
    public static Bitmap getBitmapByUrl(Uri uri, ContentResolver cr){

        Bitmap bitmap = null;
        try {
            bitmap = BitmapFactory.decodeStream(cr.openInputStream(uri));
        }catch (FileNotFoundException e){
            e.printStackTrace();
            bitmap = null;
        }
        return  bitmap;
    }

    //
    @SuppressLint("SimpleDateFormat")
    public static String getDateFormatString(Date date){
        if (date==null) date = new Date();
        String formatStr = new String();
        SimpleDateFormat matter = new SimpleDateFormat("yyyyMMdd_HHmmss");
        formatStr = matter.format(date);
        return  formatStr;
    }
}
