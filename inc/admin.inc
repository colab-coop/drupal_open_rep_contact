<?php

/**
 * Form callback for admin page.
 * @param $form
 * @param $form_state
 */
function open_rep_contact_add_block_form($form, &$form_state) {
  $form = array();
  $orcs_markup = 'No ORC blocks yet created.';
  $orcs = open_rep_contact_get_widgets();
  if ($orcs) {
    $header = array(
      'title' => t('Title'),
      'machine_name' => t('Machine Name'),
      'edit' => t('Link'),
    );
    $rows = array();
    foreach ($orcs as $name => $orc) {
      $rows[] = array(
        'title' => $orc['title'],
        'machine_name' => $name,
        'edit' => l('edit', "admin/structure/block/manage/open_rep_contact/{$name}/configure"),
      );
    }
    $orcs_markup = theme('table', array('header' => $header, 'rows' => $rows));
  }

  $form['configure_settings'] = array(
    '#title' => t('Other Settings'),
    '#prefix' => '<h3>',
    '#markup' => l(t('Click here to configure other module settings'), 'admin/structure/block/open_rep_contact/settings'),
    '#suffix' => '</h3>',
  );

  $form['orc_blocks'] = array(
    '#markup' => '<h3>' . t('ORC Blocks') . '</h3>' . $orcs_markup,
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('New ORC block: Choose a Title'),
    '#default_value' => '',
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Machine Name'),
    '#default_value' => '',
    '#maxlength' => 32,
    '#required' => TRUE,
    '#machine_name' => array(
      'exists' => 'open_rep_contact_block_name_exists',
      'source' => array('title'),
      'replace_pattern' => '[^0-9a-z_\-]',
      'error' => t('Please only use lowercase alphanumeric characters, underscores (_), and hyphens (-) for machine names.'
      ),
    )
  );

  $form['note'] = array(
    '#prefix' => '<p>',
    '#markup' => t("<em>Note:</em> Adding more than one Open Rep Contact block to a page is not supported and will break both ORC blocks."),
    '#suffix' => '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Add this block',
  );
  return $form;
}

/**
 * Form callback for module settings page.
 *
 * @param $form
 * @param $form_state
 */
function open_rep_contact_settings_form($form, &$form_state) {
  $form = array();

  $form['open_rep_contact_google_api_key'] = array(
    '#type' => 'textfield',
    '#description' => t("!civicmainurl about the Civic information API. !apiurl about getting an API Key. Note: you'll need to make an API Key and then enable Civic Information for that API Key.",
      array(
        '!civicmainurl' => l(t('Here\'s information'), "https://developers.google.com/civic-information/docs/v2/representatives/representativeInfoByAddress"),
        '!apiurl' => l(t('Here\'s information'), "https://developers.google.com/civic-information/docs/using_api")
      )
    ),
    '#title' => t('Google API Key'),
    '#default_value' => variable_get('open_rep_contact_google_api_key', ''),
    '#maxlength' => 144,
    '#size' => 60,
    '#required' => TRUE,
  );

  $form['open_rep_contact_google_analytics_id'] = array(
    '#title' => t('Google Analytics ID'),
    '#type' => 'textfield',
    '#description' => t("The Open Rep Connect app can track the steps users complete if a Google Analytics ID is provided. If your site uses Analytics ID, it must also be provided here to be used to track actions taken. Find your Google Analytics ID using instructions !trackignidurl. They are of the form @idexample. Paste in the whole code.",
      array(
        '!trackignidurl' => l(t('here'), "https://support.google.com/analytics/answer/1008080?hl=en#trackingID"),
        '@idexample' => 'UA-XXXXXXXX-X',
      )
    ),
    '#default_value' => variable_get('open_rep_contact_google_analytics_id', ''),
    '#maxlength' => 72,
    '#size' => 25,
  );

  $form['dev_settings'] = array(
    '#title' => t('Optional Developer Settings'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t("Used in case you want to store the library somewhere other than in the libraries folder, i.e., if you're compiling the app in another folder and have to version the other version."),

    'open_rep_contact_library_css_file' => array(
      '#title' => t('Alternate location for library CSS file'),
      '#type' => 'textfield',
      '#size' => 60,
      '#default_value' => variable_get('open_rep_contact_library_css_file', ''),
    ),

    'open_rep_contact_library_js_file' => array(
      '#title' => t('Alternate location for library JS file'),
      '#type' => 'textfield',
      '#size' => 60,
      '#default_value' => variable_get('open_rep_contact_library_js_file', ''),
    ),
  );

  return system_settings_form($form);
}

function open_rep_contact_add_block_form_submit($form, &$form_state) {
  $record = open_rep_contact_get_db_blob_defaults();
  $record['title'] = $form_state['values']['title'];
  $record['name'] = $form_state['values']['machine_name'];
  cache_clear_all('open_rep_contact', 'cache', TRUE);
  drupal_write_record('open_rep_contact', $record);
}

/**
 * Callback for ORC block machine_name form element. Returns TRUE if the machine_name
 * for a block exists, false otherwise.
 *
 * @param $block_name
 *
 * @return bool
 */
function open_rep_contact_block_name_exists($block_name) {
  if (open_rep_contact_get_widgets($block_name)) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Populate the BLOB database field values with empty arrays so we don't get
 * any problems because mySQL doesn't allow for defaults on BLOBs.
 *
 * @return array Record array with default values for drupal_write_record
 */
function open_rep_contact_get_db_blob_defaults() {
  $record = array();
  foreach (open_rep_contact_get_schema_blob_names() as $field_name) {
    $record[$field_name] = array();
  }
  return $record;
}