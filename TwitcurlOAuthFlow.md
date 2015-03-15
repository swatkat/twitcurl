## Getting consumer key and secret ##
  * Register your app at http://dev.twitter.com/apps/new and get consumer key/secret from twitter


## OAuth flow using twitCurl ##
Step 0: Set consumer key and secret in twitCurl object using `twitCurl::getOAuth()::setConsumerKey()` and `twitCurl::getOAuth()::setConsumerSecret()` methods.

Step 1: Get request token and secret using `twitCurl::oAuthRequestToken()` method.

Step 2: Method `twitCurl::oAuthRequestToken()` gives back a URL, which a user needs to visit and authorize your app. You now have two options:
  * Redirect user to this link (for ex: via web browser) and get the PIN. Set this PIN into `twitCurl` object using `twitCurl::getOAuth()::setOAuthPin()` method.
  * Or, use `twitCurl::oAuthHandlePIN()` and pass the URL obtained earlier to this method. `twitCurl::oAuthHandlePIN()` queries twitter, gets the PIN and authenticates the user. User is not required to visit URL or do anything else out-of-band. Note that user's twitter username and password are required for this method. They must be stored in `twitCurl` object via `twitCurl::setTwitterUsername()` and `twitCurl::setTwitterPassword()` beforehand.

Step 3: Exchange request token with access token by calling `twitCurl::oAuthAccessToken()` method.

Step 4: Get access token key and secret from twitCurl object using `twitCurl::getOAuth()::getOAuthTokenKey()` and `twitCurl::getOAuth()::getOAuthTokenSecret()` methods. Save access key and secret in a file or Registry (in case of Windows).

Note:
  * If you save the access token key and secret, then you can set these into twitCurl object in step 0, using `twitCurl::getOAuth()::setOAuthTokenKey()` and `twitCurl::getOAuth()::setOAuthTokenSecret()` methods. In this case, steps 1 through 4 can skipped during subsequent runs.

  * Checkout an example client at `http://twitcurl.googlecode.com/svn/trunk/twitterClient`. Windows executable can be downloaded from "Downloads" section.