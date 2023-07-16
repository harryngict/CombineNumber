package org.cocos2dx.cpp;

import android.app.Activity;
import android.graphics.Color;
import android.view.View;
import android.widget.FrameLayout;
import androidx.annotation.NonNull;

import com.boring.combinenumber.R;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;

public class AndroidAdManager {
    private Activity activity;
    private static AdView bottom_bannerView;
    private static boolean bottom_bannerViewShowing = false;
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
        hideBanner(bottom_bannerView);
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
        bottom_bannerView.setAdSize(AdSize.BANNER);
        bottom_bannerView.setAdUnitId(bottom_bannerId);
        FrameLayout.LayoutParams bottom_adParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT, FrameLayout.LayoutParams.WRAP_CONTENT, android.view.Gravity.BOTTOM|android.view.Gravity.CENTER_HORIZONTAL);
        bottom_bannerView.setBackgroundColor(Color.BLACK);
        bottom_bannerView.setBackgroundColor(0);
        activity.addContentView(bottom_bannerView, bottom_adParams);
    }

    public void hideBanner(AdView adView) {
        if (adView != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (adView.isEnabled()) {
                        adView.setEnabled(false);
                    }
                    if (adView.getVisibility() != View.INVISIBLE) {
                        adView.setVisibility(View.INVISIBLE);
                    }
                }
            });
        }
    }

    private void showBottomBannerAd() {
        if (bottom_bannerView != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (!bottom_bannerViewShowing) {
                        bottom_bannerView.loadAd(new AdRequest.Builder().build());
                        bottom_bannerViewShowing = true;
                    }
                    if (!bottom_bannerView.isEnabled()) {
                        bottom_bannerView.setEnabled(true);
                    }
                    if (bottom_bannerView.getVisibility() == View.INVISIBLE) {
                        bottom_bannerView.setVisibility(View.VISIBLE);
                    }
                }
            });
        }
    }
}