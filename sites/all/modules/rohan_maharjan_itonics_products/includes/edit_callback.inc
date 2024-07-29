<?php
require_once(drupal_get_path('module', 'rohan_maharjan_itonics_products') . '/includes/product_helpers.inc');
function rohan_maharjan_itonics_products_edit_form($form, &$form_state)
{
    $id = arg(3);
    $result = db_query('SELECT * FROM {rohan_maharjan_itonics_products} WHERE id = :tid', array(':tid' => $id));
    $record = $result->fetchObject();
    $form_state['record'] = $record;

    $form['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#default_value' => $record->title,
        '#description' => t('Product Title.'),
        '#size' => 40,
        '#maxlength' => 120,
        '#required' => TRUE,
        '#weight' => 0,
    );

    $form['image'] = array(
        '#type' => 'managed_file',
        '#title' => t('Image'),
        '#description' => t('Upload a Image.'),
        '#upload_location' => 'public://products/',
        '#weight' => 1,
    );

    if (!empty($record->image)) {
        $file = file_load($record->image);
        $image_output = theme(
            'image_style',
            array(
                'style_name' => 'thumbnail',
                'path' => $file->uri,
                'alt' => $file->filename,
                'title' => $file->filename,
            )
        );
        $form['current_image'] = array(
            '#markup' => $image_output,
            '#prefix' => '<div id="current-image">',
            '#suffix' => '</div>',
            '#weight' => 2,
        );
    }

    $form['summary'] = array(
        '#type' => 'textarea',
        '#title' => t('Summary'),
        '#default_value' => $record->summary,
        '#description' => t('A brief summary of the ITONICS Product.'),
        '#rows' => 5,
        '#weight' => 4,
    );

    $form['description'] = array(
        '#type' => 'text_format',
        '#title' => t('Description'),
        '#format' => unserialize($record->description)['format'],
        '#rows' => 10,
        '#columns' => 40,
        '#default_value' => unserialize($record->description)['value'],
        '#required' => TRUE,
        '#description' => t('The detailed description of the ITONICS Product using rich text formatting.'),
        '#weight' => 5,
    );

    $form['category'] = array(
        '#type' => 'select',
        '#title' => t('Category'),
        '#default_value' => $record->category ? unserialize($record->category) : array(),
        '#options' => getCategories(),
        '#multiple' => TRUE,
        '#required' => TRUE,
        '#description' => t('Select one or more categories for the ITONICS Product.'),
        '#weight' => 6,
        '#id' => 'select-categories',
    );

    $form['type'] = array(
        '#type' => 'radios',
        '#title' => t('Type'),
        '#default_value' => $record->type,
        '#options' => getTypes(),
        '#required' => TRUE,
        '#description' => t('Select the type of the ITONICS Product.'),
        '#weight' => 7,
    );

    $form['owner_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Owner Email'),
        '#default_value' => $record->owner_email,
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#description' => t('Enter the email address of the product owner.'),
        '#weight' => 8,
    );

    $form['expiry_date'] = array(
        '#type' => 'date_popup',
        '#date_format' => 'Y-m-d',
        '#title' => t('Expiry Date'),
        '#default_value' => $record->expiry_date ?? date('Y-m-d'),
        '#required' => TRUE,
        '#description' => t('Select the expiry date of the ITONICS Product.'),
        '#weight' => 9,
        '#title_display' => 'invisible',
    );

    $form['id'] = array(
        '#type' => 'hidden',
        '#value' => $id,
        '#weight' => 10,
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#weight' => 11,
    );

    $form['#submit'][] = 'rohan_maharjan_itonics_products_edit_submit_handler';

    return $form;
}

function rohan_maharjan_itonics_products_edit_submit_handler($form, &$form_state)
{
    $record = $form_state['record'];
    edit_products_validate($form_state);

    if (empty($form_state['errors'])) {
        $id = $form_state['values']['id'];
        $title = $form_state['values']['title'];
        $description = serialize($form_state['values']['description']);
        $summary = $form_state['values']['summary'];
        $category = $form_state['values']['category'];
        $type = $form_state['values']['type'];
        $owner_email = $form_state['values']['owner_email'];
        $expiry_date = $form_state['values']['expiry_date'];

        $data = array(
            'title' => $title,
            'description' => $description,
            'summary' => $summary,
            'category' => serialize($category), 
            'type' => $type,
            'owner_email' => $owner_email,
            'expiry_date' => $expiry_date,
        );

        $data['image'] = handle_image_upload($form_state, $id);
        
        db_update('rohan_maharjan_itonics_products')
            ->fields($data)
            ->condition('id', $id)
            ->execute();

        drupal_set_message(t('Product updated!'));
    } else {
        drupal_set_message(t('Error: Please fill in all required fields.'), 'error');
    }
}

function rohan_maharjan_itonics_products_edit_block_view()
{
    if (drupal_is_front_page()) {
        return NULL;
    }
    $form = drupal_get_form('rohan_maharjan_itonics_products_edit_form');
    $block = array(
        'content' => $form,
    );
    $block['content'][] .= 'Back to Listing';
    return $block;
}

function edit_products_validate(&$form_state) {
    // Initialize an array to hold error messages
    $errors = array();

    // Validate required fields
    if (empty($form_state['values']['title'])) {
        $errors['title'] = t('Title is required.');
    }
    if (empty($form_state['values']['description'])) {
        $errors['description'] = t('Description is required.');
    }
    if (empty($form_state['values']['category'])) {
        $errors['category'] = t('Category is required.');
    }
    if (empty($form_state['values']['type'])) {
        $errors['type'] = t('Type is required.');
    }
    if (empty($form_state['values']['owner_email'])) {
        $errors['owner_email'] = t('Owner email is required.');
    } elseif (!valid_email_address($form_state['values']['owner_email'])) {
        $errors['owner_email'] = t('The email address is not valid.');
    }

    // Set errors in the form state if any
    if (!empty($errors)) {
        foreach ($errors as $field => $message) {
            form_set_error($field, $message);
        }
    }
}