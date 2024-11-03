const burgerMenuToggle = document.querySelector('.burger_menu_toggle');
const headerMenu = document.querySelector('.header_menu');

burgerMenuToggle.addEventListener('click', () => {
    headerMenu.classList.toggle('active');
});

