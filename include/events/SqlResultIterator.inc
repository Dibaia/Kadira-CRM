<?php
/*+***********************************************************************************
 * The contents of this file are subject to the vtiger CRM Public License Version 1.0
 * ("License"); You may not use this file except in compliance with the License
 * The Original Code is:  vtiger CRM Open Source
 * The Initial Developer of the Original Code is vtiger.
 * Portions created by vtiger are Copyright (C) vtiger.
 * All Rights Reserved.
 *************************************************************************************/

	#[\AllowDynamicProperties]
	class SqlResultIterator implements Iterator{
		var $result;
		var $adb;
		var $pos;
		
		function __construct($adb, $result){
			$this->result = $result;
			$this->adb = $adb;
			$this->pos = 0;
		}
		
		#[\ReturnTypeWillChange]
		public function rewind(){
			$this->pos = 0;
		}
		
		#[\ReturnTypeWillChange]
		function valid(){
			$adb = $this->adb;
			return $this->pos < $adb->num_rows($this->result);
		}
		
		#[\ReturnTypeWillChange]
		public function next(){
			$this->pos+=1;
		}
		
		#[\ReturnTypeWillChange]
		public function current(){
			$adb = $this->adb;
			$data = $adb->raw_query_result_rowdata($this->result, $this->pos);
			return new SqlResultIteratorRow($data);
		}
		
		#[\ReturnTypeWillChange]
		public function key(){
			return $this->pos;
		}
		
		
		/**
		 * Return the contents of the resultset as an array. Destroys a running iterator's state.
		 *
		 * This method will reset the iterator using the rewind method.
		 * 
		 * $copyFields specify which fields of the result to copy to the array. 
		 * If not specified the function will return values for all the fields.
		 */
		function toArray($copyFields=null){
			$adb = $this->adb;
			$this->rewind();
			
			if($copyFields===null){
				$columnData = $adb->getFieldsDefinition($this->result);
				$columnNames = array();
				foreach($columnData as $column){
					$columnNames[]=$column->name;
				}
				$copyFields = $columnNames;
			}
			
			$arr=array();
			foreach($this as $row){
				$rowArr = array();
				foreach($copyFields as $name){
					$rowArr[$name]=$row->$name;
				}
				$arr[]=$rowArr;
			}
			return $arr;
			$this->rewind();
		}
	}
	
	class SqlResultIteratorRow{
		var $data;
		
		function __construct($data){
			$this->data = $data;
		}
		
		function get($column){
			return $this->data[$column];
		}
		
		function __get($column){
			return $this->get($column);
		}
		
	}
	
	
?>
