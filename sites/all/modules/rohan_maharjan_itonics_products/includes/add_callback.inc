<?php
require_once(drupal_get_path('module', 'rohan_maharjan_itonics_products') . '/includes/product_helpers.inc');
function rohan_maharjan_itonics_products_block_view($block_name = "")
{
    if (drupal_is_front_page()) {
        return NULL;
    }
    $form = drupal_get_form('rohan_maharjan_itonics_products_form');
    $block = array(
        'content' => $form,
    );
    return $block;
}


function rohan_maharjan_itonics_products_form($form, &$form_state)
{
    $form['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#description' => t('Product Title.'),
        '#size' => 40,
        '#maxlength' => 120,
        '#required' => TRUE,
        '#weight' => 0,
    );
    $form['image'] = array(
        '#type' => 'managed_file',
        '#title' => t('Image'),
        '#upload_location' => 'public://products/',
        '#weight' => 1,
    );
    $form['summary'] = array(
        '#type' => 'textarea',
        '#rows' => 5,
        '#title' => t('Summary'),
        '#description' => t('A brief summary of the ITONICS Product.'),
        '#weight' => 2,
    );
    $form['description'] = array(
        '#type' => 'text_format',
        '#title' => t('Description'),
        '#format' => 'full_html',
        '#required' => TRUE,
        '#description' => t('The detailed description of the ITONICS Product using rich text formatting.'),
        '#weight' => 3,
    );
    $form['category'] = array(
        '#type' => 'select',
        '#title' => t('Category'),
        '#options' => getCategories(),
        '#multiple' => TRUE,
        '#required' => TRUE,
        '#description' => t('Select one or more categories for the ITONICS Product.'),
        '#weight' => 4,
        '#id' => 'select-categories',
        // '#attributes' => array(
        //     'class' => array('rohan-maharjan-itonics-products-category-select'), 
        // ),
        // '#attached' => array(
        //     'js' => array(
        //         // drupal_get_path('module', 'rohan_maharjan_itonics_products') . '/select2-init.js',
        //     ),
        // ),
    );
    $form['type'] = array(
        '#type' => 'radios',
        '#title' => t('Type'),
        '#options' => getTypes(),
        '#default_value' => 'type_1',
        '#required' => TRUE,
        '#description' => t('Select the type of Product.'),
        '#weight' => 5,
    );
    $form['owner_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Owner Email'),
        '#size' => 40,
        '#maxlength' => 255,
        '#required' => TRUE,
        '#description' => t('Enter the email address of the product owner.'),
        '#weight' => 6,
    );
    $form['expiry_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('Expiry Date'),
        '#date_format' => 'Y-m-d',
        '#description' => t('Select the expiry date of Product.'),
        '#showCloseButton' => TRUE,
        '#weight' => 7,
        '#title_display' => 'invisible',
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#weight' => 8,
    );
    $form['#submit'][] = 'rohan_maharjan_itonics_products_submit_handler';

    return $form;
}


function rohan_maharjan_itonics_products_submit_handler($form, &$form_state)
{
    add_products_validate($form, $form_state);

    if(empty($form_state['errors'])) {
        $title = $form_state['values']['title'];
        $description = serialize($form_state['values']['description']);
        $summary = $form_state['values']['summary'];
        $category = $form_state['values']['category'];
        $type = $form_state['values']['type'];
        $owner_email = $form_state['values']['owner_email'];
        $expiry_date = $form_state['values']['expiry_date'];
        $image = handle_image_upload($form_state);

        db_insert('rohan_maharjan_itonics_products')
            ->fields(
                array(
                    'title' => $title,
                    'description' => $description,
                    'summary' => $summary,
                    'category' => serialize($category),
                    'type' => $type,
                    'owner_email' => $owner_email,
                    'expiry_date' => $expiry_date,
                    'image' => $image,
                )
            )
            ->execute();
        drupal_set_message(t('Product added.'));
    }
}


function add_products_validate($form, &$form_state) {
    $errors = array();

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

    if (!empty($errors)) {
        form_set_error(NULL, implode('<br>', $errors));
    }
}