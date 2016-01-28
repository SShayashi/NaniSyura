/****************************************************************************
Copyright (c) 2015 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import jp.basicinc.gamefeat.android.sdk.controller.GameFeatAppController;
import org.cocos2dx.lib.Cocos2dxActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.LinearLayout;
import android.content.Intent;
import com.sdkbox.plugin.SDKBox;
import android.content.Intent;
import com.sdkbox.plugin.SDKBox;

public class AppActivity extends Cocos2dxActivity {
    private static LinearLayout container;
    private static AppActivity me = null;
    static GameFeatAppController gfAppController;

    /////////////////////////////////
    // GAMEFEAT ICON
    /////////////////////////////////

    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        me = this;
        container = new LinearLayout(me);
        me.addContentView(container, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT));

        gfAppController = new GameFeatAppController();
        // 広告設定初期化
        gfAppController.activateGF(me, true, true, true);

        /* Chartboost  */
        onLoadNativeLibraries();
        SDKBox.init(this);
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(!SDKBox.onActivityResult(requestCode, resultCode, data)) {
            super.onActivityResult(requestCode, resultCode, data);
        }
    }

    @Override
    public void onStart() {
        super.onStart();
        SDKBox.onStart();
    }
    @Override
    protected void onStop() {
        super.onStop();
        SDKBox.onStop();
    }
    @Override
    protected void onResume() {
        super.onResume();
        SDKBox.onResume();
    }
    @Override
    protected void onPause() {
        super.onPause();
        SDKBox.onPause();
    }
    @Override
    public void onBackPressed() {
        if(!SDKBox.onBackPressed()) {
            super.onBackPressed();
        }
    }




    //================================================================================
    // GAMEFEAT オファーウォール表示・非表示
    //================================================================================
    public static void showGameFeatJNI()
    {
        gfAppController.show(me);
    }



}



