<?php

function getCategories() {
    $categories = array(
        'electronics' => 'Electronics',
        'clothing' => 'Clothing',
        'home_appliances' => 'Home Appliances',
        'toys' => 'Toys',
        'books' => 'Books',
    );
    return $categories;
}

function getTypes() {
    $types = array(
        'smartphones' => 'Smartphones',
        'laptops' => 'Laptops',
        'tablets' => 'Tablets',
        'accessories' => 'Accessories',
        'wearables' => 'Wearables',
    );
    return $types;
}

function format_and_join($type)
{
    $string = array_map(function ($type) {
        return ucfirst(str_replace('_', ' ', $type));
    }, array_keys(unserialize($type)));

    return implode(',', $string);
}

function handle_image_upload($form_state, $id = NULL, $directory = 'public://products/') {
    $file = file_save_upload(
        'image',
        array(
            'file_validate_is_image' => array(),
            'file_validate_extensions' => array('jpg jpeg png'),
        )
    );

    if ($file) {
        $file = file_move($file, $directory);

        if ($file) {
            $fid = $file->fid;

            if ($id) {
                $result = db_query('SELECT image FROM {rohan_maharjan_itonics_products} WHERE id = :id', array(':id' => $id));
                $record = $result->fetchObject();

                if ($record && isset($record->image)) {
                    $old_file = file_load($record->image);
                    if ($old_file) {
                        file_delete($old_file);
                    }
                }
            }

            return $fid;
        }
    }

    return 0;
}