/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2010 Thomas Martitz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

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



import android.content.DialogInterface;

public class RockboxActivity extends Activity 
{
    private RockboxApp RockboxAppSetting = RockboxApp.getInstance();
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        if (RockboxAppSetting.getTitlebarStatus())
        {
            getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                    WindowManager.LayoutParams.FLAG_FULLSCREEN);
        }
        Intent intent = new Intent(this, RockboxService.class);
        intent.setAction(Intent.ACTION_MAIN);
        intent.putExtra("callback", new ResultReceiver(new Handler(getMainLooper())) {
            private boolean unzip = false;
            private ProgressDialog loadingdialog;
            private void createProgressDialog()
            {
                loadingdialog = new ProgressDialog(RockboxActivity.this);
                loadingdialog.setMessage(getString(R.string.rockbox_extracting));
                loadingdialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
                loadingdialog.setIndeterminate(true);
                loadingdialog.setCancelable(false);
                loadingdialog.show();
            }

            @Override
            protected void onReceiveResult(final int resultCode, final Bundle resultData)
            {
                RockboxFramebuffer fb;
                switch (resultCode) {
                    case RockboxService.RESULT_INVOKING_MAIN:
                        if (loadingdialog != null)
                            loadingdialog.dismiss();
                        fb = new RockboxFramebuffer(RockboxActivity.this);
                        setContentView(fb);
                        fb.requestFocus();
                        break;
                    case RockboxService.RESULT_LIB_LOAD_PROGRESS:
                        if (loadingdialog == null)
                            createProgressDialog();
                        loadingdialog.setIndeterminate(false);
                        loadingdialog.setMax(resultData.getInt("max", 100));
                        loadingdialog.setProgress(resultData.getInt("value", 0));
                        break;
                    case RockboxService.RESULT_LIB_LOADED:
                        unzip = resultData.getBoolean("unzip");
                        break;
                    case RockboxService.RESULT_SERVICE_RUNNING:
                        if (!unzip) /* defer to RESULT_INVOKING_MAIN */
                        {
                            fb = new RockboxFramebuffer(RockboxActivity.this);
                            setContentView(fb);
                            fb.requestFocus();
                        }
                        setServiceActivity(true);
                        break;
                    case RockboxService.RESULT_ERROR_OCCURED:
                        Toast.makeText(RockboxActivity.this, resultData.getString("error"), Toast.LENGTH_LONG).show();
                        break;
                    case RockboxService.RESULT_ROCKBOX_EXIT:
                        finish();
                        break;
                }
            }
        });
        startService(intent);
        if (RockboxAppSetting.getRunStatus())
        {
            new AlertDialog.Builder(this)
                .setTitle(R.string.rockbox_firstrun_title)
                .setMessage(R.string.rockbox_firstrun_message)
                .setPositiveButton(R.string.OK, null)
                .show();
        }
    }
    
    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        menu.clear();
        menu.add(0, 0, 0, R.string.rockbox_simulatebutton);
        menu.add(0, 1, 0, R.string.rockbox_preference);
        menu.add(0, 4, 0, R.string.rockbox_save_eq);
        menu.add(0, 5, 0, R.string.rockbox_tinycovermaker);
        menu.add(0, 2, 0, R.string.rockbox_about);
        menu.add(0, 3, 0, R.string.rockbox_exit);        
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        final tinyCoverMaker tcm = new tinyCoverMaker(); 
        switch (item.getItemId())
        {
            case 5:
              
                final CharSequence[] items = {" 64x64 "," 96x96 ","128x128"};

                new AlertDialog.Builder(this)
                         .setTitle(R.string.rockbox_select_icon_size)
                         .setSingleChoiceItems(items, -1, new DialogInterface.OnClickListener() {
                              public void onClick(DialogInterface dialog, int item) {
                              int iconSize,result;
                              switch(item)
                              {
                                  case 0:
                                      tcm.setIconSize(64);  
                                  break;
                                  case 1:
                                      tcm.setIconSize(96);
                                  break;
                                  case 2:
                                      tcm.setIconSize(128);
                                  break;
                              }
                              Thread thr1 = new Thread(tcm);
                              thr1.start();
                              try { 
                                  thr1.join();
                              } catch (InterruptedException e) {}
                              popMessage(tcm.getResult());  
                              dialog.dismiss();    
                              }
                          }) 
                         .show();  
                break; 
            case 4:
                try {
                RockboxFramebuffer.buttonHandler(85, true); //press
                Thread.sleep(100);
                RockboxFramebuffer.buttonHandler(85, false); //release
                Thread.sleep(300);
                new AlertDialog.Builder(this)
                                .setTitle(R.string.rockbox_save_eq)
            	                .setMessage(R.string.rockbox_save_eq_ok)
            	                .setPositiveButton(R.string.OK, null)
            	                .show(); 
                tcm.saveEQ(); 
                
                RockboxFramebuffer.buttonHandler(85, true); //press
                Thread.sleep(100);
                RockboxFramebuffer.buttonHandler(85, false); //release

                } catch (InterruptedException e) {}
                break;            
            case 3:
		        RockboxNativeInterface.powerOff();
		        new Thread("Power-Off"){
		            @Override
		            public void run(){
			            try {
                            Thread.sleep(3500); //确保退出
                        } catch (InterruptedException ignored) { }
		                android.os.Process.killProcess(android.os.Process.myPid());
                    }
		        }.start();
                break;
            case 2:
                new AlertDialog.Builder(this)
            	                .setTitle(R.string.rockbox_about_title)
            	                .setMessage(R.string.rockbox_about_message)
            	                .setPositiveButton(R.string.OK, null)
            	                .show();
                break;
            case 0:
                RockboxFramebuffer.buttonHandler(0, true); //press
                try {
                    Thread.sleep(400); //线程阻塞400ms，模拟长按菜单键（WPS_MENU），小于300ms即为WPS_CONTEXT。
                } catch (InterruptedException e) {}
                RockboxFramebuffer.buttonHandler(0, false); //release
                break;
            case 1:
                Intent intent = new Intent();  
                intent.setClass(RockboxActivity.this, RockboxPref.class);  
                 /* 调用一个新的Activity */ 
                startActivity(intent);  
            	break;
         }
        return true;
     }

    private void popMessage(int result)
    {
          final String[] ResultString = {  getResources().getString(R.string.rockbox_tinycovermaker_result_1),
                                           getResources().getString(R.string.rockbox_tinycovermaker_result_2),
                                           getResources().getString(R.string.rockbox_tinycovermaker_result_3),
                                           getResources().getString(R.string.rockbox_tinycovermaker_result_4),
                                           getResources().getString(R.string.rockbox_tinycovermaker_result_5)
                                        }; 
          new AlertDialog.Builder(this)
                                .setTitle(R.string.rockbox_tinycovermaker)
            	                .setMessage(ResultString[result])
            	                .setPositiveButton(R.string.OK, null)
                                .show();
    }

    private void setServiceActivity(boolean set)
    {
        RockboxService s = RockboxService.getInstance();
        if (s != null)
            s.setActivity(set ? this : null);
    }

    public void onResume()
    {
        super.onResume();
        RockboxAppSetting.releaseWakeLock();
        setServiceActivity(true);
        setVisible(true);
        setServiceActivity(true);
    }
    
    /* this is also called when the backlight goes off,
     * which is nice 
     */
    @Override
    protected void onPause() 
    {
        super.onPause();
        RockboxAppSetting.acquireWakeLock();
        /* this will cause the framebuffer's Surface to be destroyed, enabling
         * us to disable drawing */
        setVisible(false);
    }
    
    @Override
    protected void onStop() 
    {
        super.onStop();
        setServiceActivity(false);
    }
    
    @Override
    protected void onDestroy() 
    {
        super.onDestroy();
        setServiceActivity(false);
    }
}
