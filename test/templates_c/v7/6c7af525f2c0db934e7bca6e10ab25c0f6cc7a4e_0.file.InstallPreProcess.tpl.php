<?php
/* Smarty version 4.5.3, created on 2024-07-21 10:20:23
  from '/var/www/html/vtigercrm82/layouts/v7/modules/Install/InstallPreProcess.tpl' */

/* @var Smarty_Internal_Template $_smarty_tpl */
if ($_smarty_tpl->_decodeProperties($_smarty_tpl, array (
  'version' => '4.5.3',
  'unifunc' => 'content_669cd2d71e6d69_33345879',
  'has_nocache_code' => false,
  'file_dependency' => 
  array (
    '6c7af525f2c0db934e7bca6e10ab25c0f6cc7a4e' => 
    array (
      0 => '/var/www/html/vtigercrm82/layouts/v7/modules/Install/InstallPreProcess.tpl',
      1 => 1721553536,
      2 => 'file',
    ),
  ),
  'includes' => 
  array (
  ),
),false)) {
function content_669cd2d71e6d69_33345879 (Smarty_Internal_Template $_smarty_tpl) {
?>
<input type="hidden" id="module" value="Install" />
<input type="hidden" id="view" value="Index" />
<div class="container-fluid page-container">
	<div class="row">
		<div class="col-sm-6">
			<div class="logo">
				<img src="<?php echo call_user_func_array($_smarty_tpl->registered_plugins[ 'modifier' ][ 'vimage_path' ][ 0 ], array( 'logo.png' ));?>
"/>
			</div>
		</div>
		<div class="col-sm-6">
			<div class="head pull-right">
				<h3><?php echo vtranslate('LBL_INSTALLATION_WIZARD','Install');?>
</h3>
			</div>
		</div>
	</div>
<?php }
}
