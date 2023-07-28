package org.cocos2dx.cpp;

import android.app.Activity;

import com.boring.combinenumber.R;
import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.common.GoogleApiAvailability;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.LeaderboardsClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;

public class GameHelperHelper {
    private Activity activity;
    private String leader_board_id;
    private static final int RC_LEADERBOARD_UI = 9002;

    public GameHelperHelper(Activity activity) {
        this.activity = activity;
        this.leader_board_id = activity.getBaseContext().getString(R.string.leaderboard_combine_number);
    }

    public void showLeaderboard() {
        GoogleSignInAccount signInAccount = GoogleSignIn.getLastSignedInAccount(activity);
        if (signInAccount != null) {
            displayLeaderboard(signInAccount);
        } else {
            GoogleSignInOptions gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_GAMES_SIGN_IN)
                    .build();
            GoogleSignInClient signInClient = GoogleSignIn.getClient(activity, gso);
            signInClient.silentSignIn().addOnCompleteListener(new OnCompleteListener<GoogleSignInAccount>() {
                @Override
                public void onComplete(Task<GoogleSignInAccount> task) {
                    if (task.isSuccessful()) {
                        displayLeaderboard(task.getResult());
                    } else {

                    }
                }
            });
        }
    }

    private void displayLeaderboard(GoogleSignInAccount signInAccount) {
        LeaderboardsClient leaderboardsClient = Games.getLeaderboardsClient(activity, signInAccount);
        leaderboardsClient.getLeaderboardIntent(leader_board_id)
                .addOnSuccessListener(intent -> activity.startActivityForResult(intent, RC_LEADERBOARD_UI))
                .addOnFailureListener(e -> {
                    // Handle failure to show the leaderboard
                });
    }

    public void reportScore(int score) {
        GoogleSignInAccount signInAccount = GoogleSignIn.getLastSignedInAccount(activity);
        if (signInAccount != null) {
            Games.getLeaderboardsClient(activity, signInAccount).submitScore(leader_board_id, score);
        }
    }

    public boolean isGooglePlayServicesAvailable() {
        GoogleApiAvailability apiAvailability = GoogleApiAvailability.getInstance();
        int resultCode = apiAvailability.isGooglePlayServicesAvailable(activity);
        return resultCode == ConnectionResult.SUCCESS;
    }
}