<?php

/**
 * Form callback for admin page.
 * @param $form
 * @param $form_state
 */
function open_rep_contact_admin_form($form, &$form_state) {
  //@TODO Complete this placeholder form.
  $form = array();
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'There are no settings yet.',
  );
  return $form;
}