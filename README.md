# Open Rep Contact

This module integrates the Open Rep Contact JS library with Drupal.

## Installation

Install the [Open Rep Contact library][orc] into a library directory named `open_rep_contact`
(e.g. `sites/all/libraries/open_rep_connect`) in one of two ways:

1. Download the `open_rep_contact.tgz` tarball of build files and rename the `dist` directory to the library directory.
2. Clone the project repo, install and build it, then copy the contents of the `dist` directory to the library directory.
3. Set the `open_rep_contact_google_api_key` settings via `drush vset` from the command line, or `$conf = ...` in your settings file.

A useful command for option 2 is `rsync -arv  /path/to/sevgen-twitter-widget/dist/ sites/all/libraries/open_rep_connect`
(be sure to leave the trailing slashes intact!)

Open Rep Contact is written to have minimal dependencies, so not even a specific jQuery version is required.

This module creates a block that can be used to embed the app. The easiest way to see it on a page (on
SeventhGeneration.com) is to create a page with input filter "SVG Text Replace" and content

    <!--svg_text_filter--{open_rep_contact}{open_rep_contact}-->

[orc]: https://bitbucket.org/colabcoop-ondemand/sevgen-twitter-widget/

## Customizing


To change the JS or CSS files included with the open_rep_contact library, you can set the Drupal variables
`open_rep_contact_library_js_file` or `open_rep_contact_library_css_file`. This can be especially useful if you want
to symlink to a build directory where the full app is being build as part of developing, extending, or customizing the
app code within a Drupal context. You can run `gulp` default task and rebuild the app code on watch without needing
to rsync every time. Note that you'll need to clear your cache the first time you change this variable for the new
files to be picked up. You can easily include alternate options using `$conf[varname]='path'` in your local
settings.php.

Example:
ln -s ~/www/sevgen-twitter-widget/dist  docroot/sites/all/libraries/open_rep_contact_dev
drush vset open_rep_contact_library_js_file ../open_rep_contact_dev/js/orc.bundle.js
drush vset open_rep_contact_library_css_file ../open_rep_contact_dev/css/orc-styles.css

Currently, you need to create Drupal behaviors to actually embed the app into a page. This is something we certainly
plan to change, but this module is currently mainly intended for developers. See the js files included with the module
for a template of how to set it up.