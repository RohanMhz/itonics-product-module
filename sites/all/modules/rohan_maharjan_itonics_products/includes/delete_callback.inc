<?php
function rohan_maharjan_itonics_products_delete()
{
    $id = arg(3);
    db_delete('rohan_maharjan_itonics_products')
        ->condition('id', $id, '=')
        ->execute();
    drupal_set_message(t('Product deleted.'));
    drupal_goto("admin/itonics/products/");
}