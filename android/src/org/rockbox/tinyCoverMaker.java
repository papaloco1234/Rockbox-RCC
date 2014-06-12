package org.rockbox;


import org.rockbox.Helper.Logger;
import org.rockbox.jni.RockboxNativeInterface;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.ResultReceiver;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;

import com.umeng.analytics.MobclickAgent;
import com.umeng.fb.NotificationType;
import com.umeng.fb.UMFeedbackService;

import android.os.Environment;
import java.io.File;
import java.io.FileOutputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.InputStreamReader;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.ByteArrayOutputStream;
import android.content.DialogInterface;


public class tinyCoverMaker extends Activity implements Runnable 
{
    int iconSize;
    int result;


    public int getResult()
    {
        return result;
    }


    public void saveEQ()
    {
    try {
        FileOutputStream fos = new FileOutputStream(new File(Environment.getExternalStorageDirectory(), "rockbox/eqs/eq_backup.cfg"));
        FileInputStream fis = new FileInputStream(new File(Environment.getExternalStorageDirectory(), "rockbox/config.cfg"));
        DataInputStream in = new DataInputStream(fis);
        BufferedReader br =
          new BufferedReader(new InputStreamReader(in));
        String strLine;
        while ((strLine = br.readLine()) != null) {
            if (strLine.startsWith("eq") || strLine.startsWith("compressor") 
                ||strLine.startsWith("replaygain"))
            {
                fos.write((strLine + "\n").toString().getBytes());
            }
        }
        in.close();
        fos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void setIconSize(int iconSize)
    {
        this.iconSize=iconSize;
    }
    
    public void run()
    {

        File cover = null;
        FileOutputStream fos; 
        BufferedReader br;
        DataInputStream in;
        FileInputStream fis;
        String strLine=null,strLine2=null,sbsNameStr=null;
        int currentapiVersion = android.os.Build.VERSION.SDK_INT;
        try{
            //find which theme is calling tinyCoverMaker
            fis = new FileInputStream(new File(Environment.getExternalStorageDirectory(), "rockbox/config.cfg"));
            in = new DataInputStream(fis);
            br = new BufferedReader(new InputStreamReader(in));
        
            while ((strLine = br.readLine()) != null) 
            {
                if ( strLine.startsWith("sbs:") )
                {  
                    String temp = strLine.split("/")[3];
                    sbsNameStr =  temp.split("\\.")[0];
                }
            }
            in.close();

            String path = Environment.getExternalStorageDirectory().toString() +"/rockbox/wps/" + sbsNameStr; 
            File src =new File(path+".sbs" );
            fis = new FileInputStream(src);
            in = new DataInputStream(fis);
            br = new BufferedReader(new InputStreamReader(in));
            File txtFile =new File(path+".sbs_new" );
            if (!txtFile.exists())
            {
                txtFile.createNewFile();
            }
            //read from old file and copy to new
            fos = new FileOutputStream(txtFile);
            while ((strLine = br.readLine()) != null)
            {
                fos.write((strLine +"\n").toString().getBytes());
                if ( strLine.startsWith("##--Generated by tinyCoverMaker--##")) //Magic string to mark where we should append new scripts
                    break;
            }  
            if (strLine == null) //in case Magic string doesn't exist
            {
                fos.write("##--Generated by tinyCoverMaker--##\n".getBytes());  
            }
            in.close();
            fos.close();

      
            if (currentapiVersion >= android.os.Build.VERSION_CODES.KITKAT)
            {
            // can only access "MUSIC" reference folder because Android 4.4.2 
            // block user from access external SD card's absolute path!
                File storageDir =new File (Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_MUSIC),"");
                if (!storageDir.exists())
                    storageDir.mkdirs();
  
                if(storageDir.isDirectory())
                {
                    File file[] = storageDir.listFiles();
                    int counter=0; 
                    for (File f : file) 
                    {
                        Thread.yield();
                    //ok let's find the cover art pic. 
                        if (f.isDirectory()) 
                        {  
                            String coverName=null;
                            String tname1 =  f.getName().toString()+".jpg";
                            String tname2 =  f.getName().toString()+".bmp";
                            String[] names = { "cover.jpg","cover.bmp",tname1,tname2,"folder.jpg","folder.bmp" };
                            if (tname1.contains("(") || tname1.contains(")") )
                            {
                                result=4;
                                return;
                                //return 4; //error, directory name should not contain round breaket. eg ( or )
                            }
                            for (int i=0;i<6;i++)
                            {
                                cover = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_MUSIC),"/"
                                                  +f.getName().toString()+"/"+ names[i]); 
                                coverName = names[i]; 
                                if (cover.exists() == true)
                                {  
                                    break;
                                }        
                            }
                            if (cover.exists() == false) // find the first picture in the folder and make it cover.
                            {
                                File subfile[] = f.listFiles();
                                for (File sf : subfile)
                                {
                                    if (sf.getName().toLowerCase().contains(".jpg") )
                                    {
                                        cover = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_MUSIC),"/"
                                                  +f.getName().toString()+"/"+ names[0]);
                                        sf.renameTo(cover);
                                        coverName = names[0]; 
                                        break;     
                                    }
                                    else if (sf.getName().toLowerCase().contains(".bmp") )
                                    {
                                        cover = new File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_MUSIC),"/"
                                                           +f.getName().toString()+"/"+ names[1]);
                                        sf.renameTo(cover);
                                        coverName = names[1];
                                        break;   
                                    }
                                } 
                            }
                            //if cover exist, decode the file to BMP and save
                            if (cover.exists() == true)
                            {     
                                Bitmap coverBmp = BitmapFactory.decodeFile(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_MUSIC)+"/"
                                                                        +f.getName().toString()+"/"+ coverName);
                                BitmapEx bmpEx = new BitmapEx(coverBmp.createScaledBitmap(coverBmp,iconSize,iconSize,true));
                            
                                File file2 = new File(path +"/"+ tname2); 
                           
 			        bmpEx.saveAsBMP(new FileOutputStream(file2));
                                //make the script into txt file
                                //e.g %?if(%ss(0,18,%LT), =,SWING HOLIC VOL.07)<%x(c1,SWING HOLIC VOL.07.bmp,0,0)|>
    		                fos = new FileOutputStream(txtFile,true);
                                String script ="%?if(%ss(0,"+ tname2.length() +",%LT), =,"+tname2.split(".bmp")[0]
                                             +")<%x(c"+counter+","+tname2+",0,0)|>"; 
    	                        fos.write((script + "\n").toString().getBytes()); 
    	                        fos.close();
                                counter++;
                            }  
                        }
                    }
                    //lets overwrite the old sbs file here
                    src =new File(path+".sbs_new" );
                    fis = new FileInputStream(src);
                    in = new DataInputStream(fis);
                    br = new BufferedReader(new InputStreamReader(in));
                    txtFile =new File(path+".sbs" );
                    fos = new FileOutputStream(txtFile);
                    while ((strLine = br.readLine()) != null)
                    {
                        fos.write((strLine +"\n").toString().getBytes());
                    }  
                    in.close();
                    fos.close();
                }
                else
                {
                    result=2;
                    return;  
                    //return 2; //error 2, cannot access storageDir!
                }
            }
            else  //versions before Kitkat
            {
                 //step1. read default music folder 
                fis = new FileInputStream(new File(Environment.getExternalStorageDirectory(), "rockbox/config.cfg"));
                in = new DataInputStream(fis);
                br = new BufferedReader(new InputStreamReader(in));
        
                while ((strLine = br.readLine()) != null) 
                {
                    if ( strLine.startsWith("start directory: ") )
                    {
                        strLine2 = strLine.split(": ")[1];
                    }
                }
                in.close();
                if (strLine2 == null)
                {
                    result=1;
                    return;
                    //return 1; //error 1, no dafault music folder
                }
                String defaultMusicFolder = strLine2;
                //step 2. get music folder list
                File storageDir = new File(defaultMusicFolder); 
        
                if(storageDir.isDirectory())
                {
                    File file[] = storageDir.listFiles();
                    int counter=0; 
                    for (File f : file) 
                    {
                        Thread.yield();
                        //ok let's find the cover art pic. 
                        if (f.isDirectory()) 
                        {  
                            String tname1 =  f.getAbsolutePath().toString().split(defaultMusicFolder)[1] +".jpg";
                            String tname2 =  f.getAbsolutePath().toString().split(defaultMusicFolder)[1] +".bmp";
                            String[] names = { "cover.jpg","cover.bmp",tname1,tname2,"folder.jpg","folder.bmp" };
                            if (tname1.contains("(") || tname1.contains(")") )
                            {
                                result=4;
                                return;  
                                //return 4; //error, directory name should not contain round breaket. eg ( or )
                            }
                            for (int i=0;i<6;i++)
                            {
                                cover = new File(f.getAbsolutePath().toString() +"/"+names[i]); 
                                if (cover.exists() == true)
                                    break;       
                            }
                            if (cover.exists() == false) // find the first picture in the folder and make it cover.
                            {
                                File subfile[] = f.listFiles();
                                for (File sf : subfile)
                                {
                                    if (sf.getName().toLowerCase().contains(".jpg") )
                                    {
                                        cover = new File(f.getAbsolutePath().toString() +"/"+names[0]);
                                        sf.renameTo(cover);  
                                        break; 
                                    }
                                    else if (sf.getName().toLowerCase().contains(".bmp") )
                                    {
                                        cover = new File(f.getAbsolutePath().toString() +"/"+names[1]);
                                        sf.renameTo(cover);
                                        break;  
                                    }
                                } 
                            }
                            //if cover exist, decode the file to BMP and save
                            if (cover.exists() == true)
                            {
                                Bitmap coverBmp = BitmapFactory.decodeFile(cover.getAbsolutePath());
                                BitmapEx bmpEx = new BitmapEx(coverBmp.createScaledBitmap(coverBmp,iconSize,iconSize,true));
                                File file2 = new File(path, tname2); 
 			        bmpEx.saveAsBMP(new FileOutputStream(file2));
                                //make the script into txt file
                                //e.g %?if(%ss(0,18,%LT), =,SWING HOLIC VOL.07)<%x(c1,SWING HOLIC VOL.07.bmp,0,0)|>
    		                fos = new FileOutputStream(txtFile,true);
                                String script ="%?if(%ss(0,"+ tname2.length() +",%LT), =,"+tname2.split(".bmp")[0]
                                                 +")<%x(c"+counter+","+tname2+",0,0)|>"; 
    	                        fos.write((script + "\n").toString().getBytes()); 
    	                        fos.close();
                                counter++;
                            }
                        }
                    }
                    //lets overwrite the old sbs file here
                    src =new File(path+".sbs_new" );
                    fis = new FileInputStream(src);
                    in = new DataInputStream(fis);
                    br = new BufferedReader(new InputStreamReader(in));
                    txtFile =new File(path+".sbs" );
                    fos = new FileOutputStream(txtFile);
                    while ((strLine = br.readLine()) != null)
                    {
                        fos.write((strLine +"\n").toString().getBytes());
                    }  
                    in.close();
                    fos.close();
                }
            }
        }catch (Exception e) {
                e.printStackTrace();
        }
        result=0;
        return;        
    }

}
