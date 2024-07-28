
<?php
require_once(drupal_get_path('module', 'rohan_maharjan_itonics_products') . '/includes/product_helpers.inc');
function rohan_maharjan_itonics_products_view($product_id)
{
    $query = db_select('rohan_maharjan_itonics_products')
            ->fields('rohan_maharjan_itonics_products')
            ->condition('id', $product_id)
            ->execute();

    $product =  $query->fetchObject();

    if (!$product) {
        return drupal_not_found();
    }
    $output = array();
    $output[] = array(
        '#type' => 'markup',
        '#markup' => '<p>Title:' . check_plain($product->title) . '</p>',
    );
    $output[] = array(
        '#type' => 'markup',
        '#markup' => '<p>summary:' . check_plain($product->summary) . '</p>',
    );
    $output[] = array(
        '#type' => 'markup',
        '#markup' => '<div>Description:' . unserialize($product->description)['value'] . '</div>',
    );
    $output[] = array(
        '#type' => 'markup',
        '#markup' => '<p>Category: ' . check_plain(format_and_join($product->category)) . '</p>',
    );
    $output[] = array(
        '#type' => 'markup',
        '#markup' => '<p>Type: ' . check_plain(ucfirst(str_replace('_', ' ', $product->type))) . '</p>',
    );
    $output[] = array(
        '#type' => 'markup',
        '#markup' => '<p>Owner Email: ' . check_plain($product->owner_email) . '</p>',
    );
    $output[] = array(
        '#type' => 'markup',
        '#markup' => '<p>Expiry Date: ' . check_plain($product->expiry_date) . '</p>',
    );
    $image_output = '';
    if (!empty($product->image)) {
        $file = file_load($product->image);
        $image_output = theme(
            'image_style',
            array(
                'style_name' => 'thumbnail',
                'path' => $file->uri,
                'alt' => $file->filename,
                'title' => $file->filename,
            )
        );
    }
    if (!empty($image_output)) {
        $output[] = array(
            '#markup' => $image_output,
        );
    }
    return $output;
}