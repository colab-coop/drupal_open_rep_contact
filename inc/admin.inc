<?php

/**
 * Form callback for admin page.
 * @param $form
 * @param $form_state
 */
function open_rep_contact_admin_form($form, &$form_state) {
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

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Add this block',
  );
  return $form;
}

function open_rep_contact_admin_form_submit($form, &$form_state) {
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
  $schema = drupal_get_schema('open_rep_contact');
  $record = array();
  foreach ($schema['fields'] as $field_name => $field) {
    if ($field['type'] == 'blob') {
      $record[$field_name] = array();
    }
  }
  return $record;
}