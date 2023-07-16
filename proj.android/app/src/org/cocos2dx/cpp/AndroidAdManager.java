package org.cocos2dx.cpp;

import android.app.Activity;
import android.graphics.Color;
import android.view.View;
import android.widget.FrameLayout;
import androidx.annotation.NonNull;

import com.boring.combinenumber.R;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;

public class AndroidAdManager extends AdListener {
    private Activity activity;
    private static AdView bottom_bannerView = null;
    private String bottom_bannerId;
    private String interstitialId;

    public AndroidAdManager(Activity activity) {
        this.activity = activity;
        bottom_bannerId = activity.getBaseContext().getString(R.string.bannerId);
        interstitialId = activity.getBaseContext().getString(R.string.interstitialId);
        setupAdBannerView();
    }

    public void onDestroy() {
        bottom_bannerView.destroy();
    }

    public void showBannerAd() {
        showBottomBannerAd();
    }

    public void hideBanner() {
        hideAdView(bottom_bannerView);
    }

    public boolean isBannerViewVisible() {
        if(bottom_bannerView == null) {
            return false;
        } else {
            return bottom_bannerView.getVisibility() == View.VISIBLE;
        }
    }

    public void showInterstitial() {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                InterstitialAd.load(activity, interstitialId, new AdRequest.Builder().build(), new InterstitialAdLoadCallback() {
                    @Override
                    public void onAdLoaded(@NonNull InterstitialAd interstitialAd) {
                        interstitialAd.show(activity);
                    }
                    @Override
                    public void onAdFailedToLoad(@NonNull LoadAdError loadAdError) {
                    }
                });
            }
        });
    }

    private void setupAdBannerView() {
        setupBottomAdView();
        hideBanner();
    }

    private void setupBottomAdView() {
        bottom_bannerView = new AdView(activity);
        bottom_bannerView.setAdSize(AdSize.FULL_BANNER);
        bottom_bannerView.setAdListener(this);
        bottom_bannerView.setAdUnitId(bottom_bannerId);
        FrameLayout.LayoutParams bottom_adParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT, FrameLayout.LayoutParams.WRAP_CONTENT, android.view.Gravity.BOTTOM|android.view.Gravity.CENTER_HORIZONTAL);
        bottom_bannerView.setBackgroundColor(Color.BLACK);
        bottom_bannerView.setBackgroundColor(0);
        bottom_bannerView.setEnabled(false);
        bottom_bannerView.setVisibility(View.INVISIBLE);
        activity.addContentView(bottom_bannerView, bottom_adParams);
    }

    public void hideAdView(AdView adView) {
        if (adView != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    adView.setEnabled(false);
                    adView.setVisibility(View.INVISIBLE);
                }
            });
        }
    }

    private void showBottomBannerAd() {
        if (bottom_bannerView != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    bottom_bannerView.loadAd(new AdRequest.Builder().build());
                }
            });
        }
    }

    public void onAdFailedToLoad(@NonNull LoadAdError var1) {
        bottom_bannerView.setEnabled(false);
        bottom_bannerView.setVisibility(View.INVISIBLE);
    }

    public void onAdLoaded() {
        bottom_bannerView.setEnabled(true);
        bottom_bannerView.setVisibility(View.VISIBLE);
    }
}