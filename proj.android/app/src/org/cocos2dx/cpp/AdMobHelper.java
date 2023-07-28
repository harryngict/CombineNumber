package org.cocos2dx.cpp;

import android.app.Activity;
import android.graphics.Color;
import android.view.Gravity;
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

public class AdMobHelper extends AdListener {
    private Activity activity;
    private static AdView bannerView = null;
    private String bannerId;
    private String interstitialId;

    public AdMobHelper(Activity activity) {
        this.activity = activity;
        bannerId = activity.getBaseContext().getString(R.string.bannerId);
        interstitialId = activity.getBaseContext().getString(R.string.interstitialId);
        setupAdBannerView();
    }

    public void onDestroy() {
        bannerView.destroy();
    }

    public void showBannerAd() {
        showBannerViewAtBottom();
    }

    public void hideBanner() {
        hideAdView(bannerView);
    }

    public boolean isBannerViewVisible() {
        if (bannerView == null) {
            return false;
        } else {
            return bannerView.getVisibility() == View.VISIBLE;
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
        setupBannerView();
        hideBanner();
    }

    private void setupBannerView() {
        bannerView = new AdView(activity);
        bannerView.setAdSize(AdSize.FULL_BANNER);
        bannerView.setAdListener(this);
        bannerView.setAdUnitId(bannerId);
        bannerView.setBackgroundColor(Color.BLACK);
        bannerView.setBackgroundColor(0);
        bannerView.setEnabled(false);
        bannerView.setVisibility(View.INVISIBLE);

        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(
                FrameLayout.LayoutParams.WRAP_CONTENT,
                FrameLayout.LayoutParams.WRAP_CONTENT,
                Gravity.BOTTOM
        );
        activity.addContentView(bannerView, layoutParams);
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

    private void showBannerViewAtBottom() {
        if (bannerView != null) {
            activity.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    bannerView.loadAd(new AdRequest.Builder().build());
                }
            });
        }
    }

    public void onAdFailedToLoad(@NonNull LoadAdError var1) {
        bannerView.setEnabled(false);
        bannerView.setVisibility(View.INVISIBLE);
    }

    public void onAdLoaded() {
        bannerView.setEnabled(true);
        bannerView.setVisibility(View.VISIBLE);
    }
}