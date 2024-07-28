<?php 
require_once(drupal_get_path('module', 'rohan_maharjan_itonics_products') . '/includes/product_helpers.inc');
function rohan_maharjan_itonics_products_sort_with_pager_content() {
    $headers = array(
        array('data' => t('Serial Number'), 'field' => 'id', 'sort' => 'asc'),
        array('data' => t('Product Title'), 'field' => 'title'),
        array('data' => t('Product Category'), 'field' => 'category'),
        array('data' => t('Product Type'), 'field' => 'type'),
        array('data' => t('Owner Email Address'), 'field' => 'owner_email'),
        array('data' => t('Expiration Date'), 'field' => 'expiry_date'),
        array('data' => t('Product Image'), 'field' => 'image'),
        array('data' => t('Actions')),
    );

    $query = db_select('rohan_maharjan_itonics_products', 'products')
        ->fields('products', array('id', 'title', 'description', 'summary', 'category', 'type', 'owner_email', 'expiry_date', 'image'));

    $sortable_table = $query->extend('TableSort')
        ->orderByHeader($headers);

    $paginated_table = $sortable_table->extend('PagerDefault')
        ->limit(5);

    $result = $paginated_table->execute();

    $rows = format_product_rows($result);

    if (!empty($rows)) {
        $content = theme('table', array('header' => $headers, 'rows' => $rows, 'attributes' => array('id' => 'product-table')));
        $content .= theme('pager');
    } else {
        $content = t("No products found.");
    }

    $content .= l(t('Add New Product'), 'admin/itonics/products/add', array('attributes' => array('class' => array('button'))));

    return $content;
}

function format_product_rows($records) {
    $rows = array();
    $row_number = 1;

    foreach ($records as $record) {
        $image_display = '';
        if (!empty($record->image)) {
            $file = file_load($record->image);
            $image_display = theme(
                'image_style',
                array(
                    'style_name' => 'thumbnail',
                    'path' => $file->uri,
                    'alt' => $file->filename,
                    'title' => $file->filename,
                )
            );
        }

        $rows[] = array(
            'data' => array(
                $row_number,
                $record->title,
                format_and_join($record->category),
                ucfirst(str_replace('_', ' ', $record->type)),
                $record->owner_email,
                $record->expiry_date,
                $image_display,
                l('View', 'admin/itonics/products/' . $record->id) . ' | ' . l('Edit', 'admin/itonics/products/' . $record->id . '/edit') . ' | ' . l('Delete', 'admin/itonics/products/' . $record->id . '/delete')
            )
        );
        $row_number++;
    }

    return $rows;
}

