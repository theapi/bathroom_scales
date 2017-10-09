<?php
namespace Theapi\Datalogger;

interface InputArgumentInterface {

  /**
   * The name of the value.
   * @return string
   */
  public function getName();

  /**
   * The php filter options used to verify the input.
   */
  public function getFilterOptions();

  /**
   * The php filter options used to verify the input.
   */
  public function setFilterOptions($options);

  /**
   * The php filter.
   * @return int
   */
  public function getFilter();

  /**
   * The php filter.
   * @return self
   */
  public function setFilter($filter);

  /**
   * The value that needs to be verified.
   * @return self
   */
  public function setValue($value);

  /**
   * The value that needs to be verified.
   * @return mixed
   */
  public function getValue($value);
}
