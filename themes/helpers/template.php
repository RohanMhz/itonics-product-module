<?php

function format_and_join($type) {
    $string = array_map(function ($type) {
        return ucfirst(str_replace('_', ' ', $type));
    }, array_keys(unserialize($type)));

    return implode(',', $string);
}

function render_image($image_id) {
    if (empty($image_id)) {
        return '';
    }

    $file = file_load($image_id);
    return theme(
        'image_style',
        array(
            'style_name' => 'thumbnail',
            'path' => $file->uri,
            'alt' => $file->filename,
            'title' => $file->filename,
        )
    );
}

function generate_action_links($product_id) {
    return l('View', 'admin/itonics/products/' . $product_id) . ' | ' . 
           l('Edit', 'admin/itonics/products/' . $product_id . '/edit') . ' | ' . 
           l('Delete', 'admin/itonics/products/' . $product_id . '/delete');
}
