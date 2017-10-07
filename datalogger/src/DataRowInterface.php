<?php
namespace Theapi\Datalogger;

interface DataRowInterface {

  /**
   * @param $value
   *
   * @return self
   */
  public function setBattery($value);

  /**
   * @param $value
   *
   * @return self
   */
  public function setPerson($value);

  /**
   * Set the timestamp to now.
   *
   * @return self
   */
  public function setTimestamp();

  /**
   * @param $value
   *
   * @return self
   */
  public function setWeight($value);

  /**
   * The Voltage on the battery.
   * @return int
   */
  public function battery();

  /**
   * The name of the person.
   * @return string
   */
  public function person();

  /**
   * The date time in ISO 8601 format.
   * @return string
   */
  public function timestamp();

  /**
   * The weight in Kg.
   * @return float
   */
  public function weight();

}
