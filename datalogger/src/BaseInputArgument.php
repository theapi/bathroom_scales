<?php

namespace Theapi\Datalogger;


class BaseInputArgument implements InputArgumentInterface {

  protected $value;

  protected $options;

  protected $filter;

  /**
   * @inheritDoc
   */
  public function getName() {
    return 'Base';
  }

  /**
   * @inheritDoc
   */
  public function setValue($value) {
    $this->value = $value;

    return $this;
  }

  /**
   * @inheritDoc
   */
  public function getValue($value) {
    return $this->value;
  }

  /**
   * @inheritDoc
   */
  public function getFilterOptions() {
    return $this->options;
  }

  /**
   * @inheritDoc
   */
  public function setFilterOptions($options) {
    $this->options = $options;
  }

  /**
   * @inheritDoc
   */
  public function getFilter() {
    return $this->filter;
  }

  /**
   * @inheritDoc
   */
  public function setFilter($filter) {
    $this->filter = $filter;
  }

}
