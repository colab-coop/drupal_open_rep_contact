# Open Rep Contact

This module integrates the Open Rep Contact JS library with Drupal.

## How it Works

This module allows you to place blocks that become "tweet to your representative" widgets on drupal pages.

It connects with the Google Civic Information API and allows some parameters to be configured.

For instance, you could set up an action contacting state legislature members, or you could use it
to contact senators. You could set up your own custom tweets and customize it heavily.

Multiple blocks can be configured, but two blocks cannot appear on the same page.

## Installation

Install the [Open Rep Contact library][orc] into a library directory named `open_rep_contact`
(e.g. `sites/all/libraries/open_rep_connect`) in one of two ways:

1. Download or clone the [Open Rep Contact JS App](https://github.com/colab-coop/open-rep-contact.js) and move/rename the `dist` directory to exist at `libraries/open_rep_connect`. Once complete, you will have three directories at `libraries/open_rep_connect`: `css`, `js`, and `img`.
3. Add a block and the google API key at Structure -> Blocks -> Open Rep Connect Instances (tab)
4. Configure the block you set up using the "edit" link
5. Add your block to the page.

Open Rep Contact has minimal dependencies, jQuery is not required.

## For Developers

To change the JS or CSS files included with the open_rep_contact library, you can set the Drupal variables
`open_rep_contact_library_js_file` or `open_rep_contact_library_css_file`. This can be especially useful if you want
to symlink to a build directory where the full app is being build as part of developing, extending, or customizing the
app code within a Drupal context. You can run `gulp` default task and rebuild the app code on watch without needing
to rsync every time. Note that you'll need to clear your cache the first time you change this variable for the new
files to be picked up. You can easily include alternate options using `$conf[varname]='path'` in your local
settings.php.

Example:
ln -s ~/www/my_app_location/dist  docroot/sites/all/libraries/open_rep_contact_dev
drush vset open_rep_contact_library_js_file ../open_rep_contact_dev/js/orc.bundle.js
drush vset open_rep_contact_library_css_file ../open_rep_contact_dev/css/orc-styles.css