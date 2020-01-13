<?php
/**
 * @file
 * Serial (Fields Helper).
 */

/**
 * Class SerialFields.
 */
class SerialFields {

  private $fields = array();
  private $instances = array();

  /**
   * Set field definitions.
   *
   * @param array[] $fields
   *   An associative array where keys - field names and values - definition.
   */
  public function __construct(array $fields) {
    $this->fields = $fields;
  }

  /**
   * Create fields.
   *
   * @return self
   *   Object instance.
   *
   * @throws \FieldException
   *   When cannot create a field.
   */
  public function create() {
    foreach ($this->fields as $name => $data) {
      if (!db_table_exists("field_data_$name")) {
        field_create_field($data + array(
          'default' => '',
          'not null' => TRUE,
          'field_name' => $name,
        ));
      }
    }

    return $this;
  }

  /**
   * Attach existing fields into entity.
   *
   * @param string $entity_type
   *   Entity machine name.
   * @param string $bundle_name
   *   Entity bundle name.
   *
   * @return self
   *   Object instance.
   *
   * @throws \FieldException
   *   When instance cannot be created.
   */
  public function attach($entity_type, $bundle_name) {
    $attached_fields = field_info_instances($entity_type, $bundle_name);

    foreach ($this->fields as $field_name => $data) {
      if (empty($attached_fields[$field_name]) && field_info_field($field_name)) {
        // Provide a possibility to specify field weight, depending on
        // another one.
        //
        // @code
        // $fields = array(
        //   'field_title' => array(
        //     'type' => 'text',
        //     'label' => 'Title',
        //     'widget' => array(
        //       'weight' => 10,
        //     ),
        //   ),
        //   'field_description' => array(
        //     'type' => 'text',
        //     'label' => 'Description',
        //     'widget' => array(
        //       // Weight of this field will be "9".
        //       'weight' => array('field_title', -1),
        //     ),
        //   ),
        // );
        // @endcode
        if (isset($data['widget']['weight']) && is_array($data['widget']['weight'])) {
          list($dependent, $calc) = $data['widget']['weight'];

          $dependent = field_info_instance($entity_type, $dependent, $bundle_name);

          if (!empty($dependent)) {
            $data['widget']['weight'] = $dependent['widget']['weight'] + $calc;
          }
        }

        field_create_instance($data + array(
          'bundle' => $bundle_name,
          'field_name' => $field_name,
          'entity_type' => $entity_type,
        ));
      }
    }

    return $this;
  }

}
