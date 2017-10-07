<?php
namespace Theapi\Datalogger;

interface DataInterface {

  /**
   * Set a value.
   * @param string $key
   *
   * @return self
   */
  public function setValue($key, $value);

  /**
   * Get a value.
   *
   * @return string
   */
  public function getValue($key);

  public function toCSV();

  public function toString();

}
